/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include <Windows.h>
#include <GL/GL.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "texturemanager.h"
#include "color.h"
#include "blood.h"


// ---------- PARTICLE ----------

// update - a részecske mozgatása, animálása, miegyéb; paraméter a deltaTime és a részecskére ható erő
void cBloodParticle::update(float dt, const sf::Vector2f &force)
{
	// öregszik, talán meg is hal, talán statikussá válik
	age += dt;
	float age_percentage = age / lifetime;
	if( age_percentage >= reachDestinyAtAge )
	{
		currentState = (destiny == cParticle::DIE) ? cParticle::UNUSED : cParticle::USED_STATIC;
		return;
	}

	// mozog, stb.
	float velocity_length = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	velocity.x /= velocity_length;
	velocity.y /= velocity_length;
	velocity_length *= 0.95f;
	velocity.x *= velocity_length;
	velocity.y *= velocity_length;

	//weight += 1.5f;
	acceleration = force / weight;
	velocity = velocity + (acceleration * dt);
	position = position + (velocity * dt);
	
	
	if( age_percentage <= 0.5f )
	{
		size += 1.0f;
	}
	else
	{
		color.A = 2 - age_percentage / 0.5f;
		if( size > 0 )
		{
			size -= 0.2f;
		}
	}
}

// ---------- EMITTER ----------

// új részecske inicializálása a paraméterül kapott indexen
void cBloodEmitter::CreateParticle(size_t index)
{
	cBloodParticle *p = (cBloodParticle*)(particles[index]);
	
	// használatban van mostantól
	p->currentState = cParticle::USED_DYNAMIC;
	
	// részecske elhelyezése
	sf::Vector2f pos((rand() % 1001) / 1000.0f * radius.x, (rand() % 1001) / 1000.0f * radius.y);
	p->position = position + pos;

	// sebesség beállítása
	float rnd;
	rnd = (rand() % 1001) / 1000.0f * (directionAngleMax - directionAngleMin) + directionAngleMin;
	p->velocity.x = (float)cos(rnd * M_PI / 180.f);
	p->velocity.y = (float)sin(rnd * M_PI / 180.f);
	rnd = (rand() % 1001) / 1000.0f * (initialVelocity_rand_max + initialVelocity_rand_min) - initialVelocity_rand_min;
	p->velocity.x *= 1 + rnd / 100.f;
	p->velocity.y *= 1 + rnd / 100.f;

	// súly
	rnd = (rand() % 1001) / 1000.0f * (weight_rand_max + weight_rand_min) - weight_rand_min;
	p->weight = weight * (1 + rnd / 100.0f);

	// elforgatottság
	p->rotation = (float)(rand() % 360);

	// élettartam és kor
	rnd = (rand() % 1001) / 1000.0f * (lifetime_rand_max + lifetime_rand_min) - lifetime_rand_min;
	p->lifetime = lifetime * (1 + rnd / 100.0f);
	p->age = 0;

	// szín - szürkeárnyalatos
	rnd = (rand() % 1001) / 1000.0f * (initialColor_rand_max + initialColor_rand_min) - initialColor_rand_min;
	p->color.R = initialColor.R * (1 + rnd / 100.0f);
	p->color.G = initialColor.G * (1 + rnd / 100.0f);
	p->color.B = initialColor.B * (1 + rnd / 100.0f);
	p->color.A = initialColor.A * (1 + rnd / 100.0f);

	// kezdő méret
	rnd = (rand() % 1001) / 1000.0f * (initialSize_rand_max + initialSize_rand_min) - initialSize_rand_min;
	p->size = initialSize * (1 + rnd / 100.0f);

	// vérdarab kiválasztása
	p->texturePortionIndex = rand() % numberOfTexturePortions;

	// a részecske sorsa a véletlenre van bízva
	p->destiny = (rand() % 100) < 30 ? cParticle::BECOME_STATIC : cParticle::DIE;
	if( p->destiny == cParticle::DIE )
	{
		p->reachDestinyAtAge = 1.f;
	}
	else
	{
		rnd = (rand() % (int)((reachDestinyAtAgeMax - reachDestinyAtAgeMin) * 1000)) / 1000.f + reachDestinyAtAgeMin;
		p->reachDestinyAtAge = rnd;
	}
}

// n darab új részecske azonnali legyártatása
void cBloodEmitter::createParticles(int n)
{
	while( n >= 1 )
	{
		// index keresése új elemnek - először a felhasználatlan részecskék között
		size_t index = particles.size();
		for( size_t i = 0, s = index; i < s; i++ )
		{
			if( particles[i]->currentState == cParticle::UNUSED )
			{
				index = i;
				break;
			}
		}

		// ha nem találtunk használható részecskét, akkor bizony keresni kell egy statikusat, amit ecélból felhasználunk
		if( index == particles.size() )
		{
			for( size_t i = 0, s = index; i < s; i++ )
			{
				if( particles[i]->currentState == cParticle::USED_STATIC )
				{
					index = i;
					break;
				}
			}

			// ha még ezek között sem találtunk, akkor használjuk a legrégebbi részecske objektumot
			if( index == particles.size() )
			{
				index = 0;
			}
		}

		// részecske létrehozása
		CreateParticle(index);

		n--;
	}
}

// az emitter frissítése
void cBloodEmitter::update(float dt)
{
	// ha kell létrehozni új részecskét bármikor is
	if( (spawningRate > 0) && (emitterLifetime > 0) )
	{
		// eltelt egy kis idő
		elapsedTime += dt;

		// ennyi új részecskét kell létrehozni
		float num_of_new_particles = elapsedTime / (1000.0f / spawningRate);
		while( num_of_new_particles >= 1 )
		{
			createParticles(1);

			elapsedTime -= 1000.0f / spawningRate;
			num_of_new_particles--;
		}
	}

	// használatban lévő részecskék frissítése
	size_t num_of_dynamic_particles = 0;
	for( size_t i = 0; i < particles.size(); i++ )
	{
		if( particles[i]->currentState == cParticle::USED_DYNAMIC )
		{
			particles[i]->update(dt, force);
			num_of_dynamic_particles++;
		}
	}

	// az emitter is öregszik
	emitterLifetime -= dt;
	if( (emitterLifetime <= 0) && (num_of_dynamic_particles == 0) )
	{
		currentState = cEmitter::UNUSED;
	}

	// emitter mozgatása
	// position = position + (force * dt);
}

// az emitter részecskéinek kirajzolása
void cBloodEmitter::Render()
{
	// használatban lévő részecskék kirajzolása
	for( size_t i = 0, s = particles.size(); i < s; i++ )
	{
		if( particles[i]->currentState != cParticle::UNUSED )
		{
			particles[i]->render();
		}
	}
}
