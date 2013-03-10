/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "bloodmanager.h"
#include "texturemanager.h"

// konstruktor
BloodManager::BloodManager()
{
	// text�ra bet�lt�se
	size_t blood_texture_index;
	int err = TextureManager::Instance().LoadTexture("Content/Sprites/blood_particle.png", blood_texture_index, 1, true);

#ifdef _DEBUG
	if( err )
	{
		printf("> ERROR! BloodManager cannot be initialized - missing texture: %s\n", "Content/Sprites/blood_particle.png");
	}
#endif

	// inicializ�lunk
	emitters.resize(INITIAL_NUM_OF_EMITTERS, nullptr);
	for( size_t i = 0; i < INITIAL_NUM_OF_EMITTERS; i++ )
	{
		emitters[i] = new cBloodEmitter(sf::Vector2f(), 80, sf::Vector2f(0, -0.02f), blood_texture_index, 0, 8, cEmitter::UNUSED, 0.2f, 0.95f, sf::Vector2f(0, 0), 0, 0);
		
		cBloodEmitter &b = *emitters[i];
		b.initialVelocity = 0.7f;
		b.initialVelocity_rand_max = 20;
		b.initialVelocity_rand_min = 20;
		b.weight = 50.0f;
		b.weight_rand_max = 10;
		b.weight_rand_min = 10;
		b.lifetime = 1000;
		b.lifetime_rand_max = 100;
		b.lifetime_rand_min = 50;
		b.initialColor = sColor4(0.5f, 0.f, 0.f, 0.5);
		b.initialColor_rand_max = 100;
		b.initialColor_rand_min = 0;
		b.initialSize = 10.f;
		b.initialSize_rand_max = 100;
		b.initialSize_rand_min = 0;
	}
}

// destruktor
BloodManager::~BloodManager()
{
	for( size_t i = 0, s = emitters.size(); i < s; i++ )
	{
		delete emitters[i];
	}
}

// v�r l�trehoz�sa a p�ly�n
void BloodManager::AddBlood(sf::Vector2f position, float lifetime, float spawningRate, float angleMin, float angleMax)
{
	// felhaszn�latlan emitter keres�se
	size_t index = emitters.size();
	for( size_t i = 0, s = index; i < s; i++ )
	{
		if( emitters[i]->currentState == cEmitter::UNUSED )
		{
			index = i;
			break;
		}
	}

	// ha nem tal�ltunk, �t kell m�retezni a vektort
	if( index == emitters.size() )
	{
		// ha el�rt�k a max m�retet, fail
		if( index == MAX_NUM_OF_EMITTERS )
		{
#ifdef _DEBUG
			printf("> WARNING! Maximal number of emitters (%d) reached. Cannot create another one... Consider increasing MAX_NUM_OF_EMITTERS.\n", MAX_NUM_OF_EMITTERS);
#endif
			return;
		}

		// �j elem hozz�ad�sa
#ifdef _DEBUG
		printf("> Increasing the size of emitters' vector by one...\n");
#endif
		emitters.push_back(nullptr);
		emitters[index] = new cBloodEmitter(*emitters[0]);
	}

	// az �j emitter elhelyez�se, inicializ�l�sa
	emitters[index]->position = position;
	emitters[index]->currentState = cEmitter::USED;
	emitters[index]->emitterLifetime = lifetime;
	emitters[index]->spawningRate = spawningRate;
	emitters[index]->directionAngleMin = angleMin;
	emitters[index]->directionAngleMax = angleMax;
}

// az �sszes v�remitter resetel�se (p�lya bet�lt�sekor pl)
void BloodManager::ResetAllEmitters()
{
	for( size_t i = 0, s = emitters.size(); i < s; i++ )
	{
		emitters[i]->currentState = cEmitter::UNUSED;
		emitters[i]->ResetAllParticles();
	}
}

// �sszes v�r-emitter friss�t�se
void BloodManager::UpdateEmitters(float dt)
{
	for( size_t i = 0, s = emitters.size(); i < s; i++ )
	{
		if( emitters[i]->currentState == cEmitter::USED )
		{
			emitters[i]->update(dt);
		}
	}
}

// v�r emitterek friss�t�se
void BloodManager::Render()
{
	for( size_t i = 0, s = emitters.size(); i < s; i++ )
	{
		emitters[i]->Render();
	}
}
