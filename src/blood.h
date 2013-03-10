/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _BLOOD_H_
#define _BLOOD_H_

#include "particle.h"
#include "emitter.h"
#include <vector>


// vér részecskék osztálya
class cBloodParticle : public cParticle
{
public :
	// konstruktor
	cBloodParticle(sf::Vector2f pos, sf::Vector2f vel, float weight, float rotation, float lifetime, sColor4 color, float size, size_t textureIndex,  unsigned short texturePortionIndex, unsigned short numberOfTexturePortions, PARTICLE_STATE state, DESTINY destiny, float reachDestinyAtAge) : cParticle(pos, vel, weight, rotation, lifetime, color, size, textureIndex, texturePortionIndex, numberOfTexturePortions, state, destiny, reachDestinyAtAge)
	{
	}

	// update - a részecske mozgatása, animálása, miegyéb; paraméter a deltaTime és a részecskére ható erő
	virtual void update(float dt, const sf::Vector2f &force);
};


// vér emitter
class cBloodEmitter : public cEmitter
{
protected :
	void CreateParticle(size_t index);											// új részecske inicializálása a paraméterül kapott indexen

public :
	
	sf::Vector2f radius;														// az emitter pozíciójától maximum ekkora távolságban jönnek létre az új részecskék (méret)
	

	// konstruktor
	cBloodEmitter(sf::Vector2f pos, float spawningRate, sf::Vector2f force, size_t textureIndex,  unsigned short texturePortionIndex, unsigned short numberOfTexturePortions, STATE state, float reachDestinyAtAgeMin, float reachDestinyAtAgeMax, sf::Vector2f radius, float angleMin, float angleMax) : cEmitter(pos, spawningRate, force, textureIndex, texturePortionIndex, numberOfTexturePortions, state, reachDestinyAtAgeMin, reachDestinyAtAgeMax, angleMin, angleMax), radius(radius)
	{
		particles.resize(INITIAL_NUM_OF_PARTICLES, NULL);

		for( size_t i = 0; i < particles.size(); i++ )
		{
			particles[i] = new cBloodParticle(sf::Vector2f(), sf::Vector2f(), 0, 0, 0, sColor4(), 0, textureIndex, texturePortionIndex, numberOfTexturePortions, cParticle::UNUSED, cParticle::DIE, 1.f);
		}
	}

	// másoló konstruktor
	cBloodEmitter(const cBloodEmitter &e) : cEmitter(e), radius(e.radius)
	{
		particles.resize(INITIAL_NUM_OF_PARTICLES, NULL);

		for( size_t i = 0; i < particles.size(); i++ )
		{
			particles[i] = new cBloodParticle(sf::Vector2f(), sf::Vector2f(), 0, 0, 0, sColor4(), 0, textureIndex, texturePortionIndex, numberOfTexturePortions, cParticle::UNUSED, cParticle::DIE, 1.f);
		}
	}

	// n darab új részecske azonnali legyártatása
	virtual void createParticles(int n);

	// az emitter frissítése
	virtual void update(float dt);

	// az emitter részecskéinek kirajzolása
	virtual void Render();
};


#endif
