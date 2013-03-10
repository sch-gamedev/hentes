/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _EMITTER_H_
#define _EMITTER_H_


#include <vector>
#include <list>

#include <SFML/System.hpp>
#include "color.h"
#include "particle.h"


// részecskekibocsátó forrás
class cEmitter
{
protected :
	std::vector<cParticle *> particles;											// a részecskéket tároló vektor
	float elapsedTime;
	static const size_t INITIAL_NUM_OF_PARTICLES = 200;							// ennyi részecske objektum van kezdetben a pool-ban


public :
	// --- emitterre vonatkozó adatok ---

	enum STATE
	{
		USED,
		UNUSED
	};
	STATE currentState;															// használatban van-e az emitter
	sf::Vector2f position;														// az emitter pozíciója
	float spawningRate;															// új részecskék/másodperc
	sf::Vector2f force;															// a rendszerre ható erő
	size_t textureIndex;														// az összes részecskéhez használt textúra index
	float emitterLifetime;														// ennyi ideig működik a rendszer

	// --- részecskékre vonatkozó adatok ---

	float initialVelocity;														// új részecskék létrehozáskori sebessége
	float initialVelocity_rand_min;
	float initialVelocity_rand_max;

	float directionAngleMin;													// a részecskék irányának (vízszintessel bezárt szög) minimuma
	float directionAngleMax;													// ... maximuma

	float weight;																// tömeg
	float weight_rand_min;
	float weight_rand_max;

	float lifetime;																// ennyi ideig él a részecske, EZREDMÁSODPERCBEN
	float lifetime_rand_min;
	float lifetime_rand_max;

	sColor4 initialColor;														// részecske színe létrehozáskor
	float initialColor_rand_min;
	float initialColor_rand_max;

	float initialSize;															// részecske mérete létrehozáskor
	float initialSize_rand_min;
	float initialSize_rand_max;

	unsigned short texturePortionIndex;											// ennyiedik részét jeleníti meg a textúrának
	unsigned short numberOfTexturePortions;										// ennyi darab részre osztottuk fel a textúrát

	float reachDestinyAtAgeMin;													// az intervallum, amelyen belül a részecske befejezi pályafutását mint dinamikus részecske
	float reachDestinyAtAgeMax;													//   0.f és 1.f közötti szám, ezen belül random lesz az érték


	// konstruktor
	cEmitter(sf::Vector2f pos, float spawningRate, sf::Vector2f force, size_t textureIndex, unsigned short texturePortionIndex, unsigned short numberOfTexturePortions, STATE state, float reachDestinyAtAgeMin, float reachDestinyAtAgeMax, float angleMin, float angleMax) : position(pos), spawningRate(spawningRate), force(force), textureIndex(textureIndex), elapsedTime(0), texturePortionIndex(texturePortionIndex), numberOfTexturePortions(numberOfTexturePortions), currentState(state), reachDestinyAtAgeMin(reachDestinyAtAgeMin), reachDestinyAtAgeMax(reachDestinyAtAgeMax), directionAngleMin(angleMin), directionAngleMax(angleMax)
	{
	}

	// másoló konstruktor
	cEmitter(const cEmitter &e) : position(e.position), spawningRate(e.spawningRate), force(e.force), textureIndex(e.textureIndex), elapsedTime(0)
	{
		initialVelocity = e.initialVelocity;
		initialVelocity_rand_min = e.initialVelocity_rand_min;
		initialVelocity_rand_max = e.initialVelocity_rand_max;

		directionAngleMin = e.directionAngleMin;
		directionAngleMax = e.directionAngleMax;
		
		weight = e.weight;					
		weight_rand_min = e.weight_rand_min;
		weight_rand_max = e.weight_rand_max;
		
		lifetime = e.lifetime;				
		lifetime_rand_min = e.lifetime_rand_min;
		lifetime_rand_max = e.lifetime_rand_max;
		
		initialColor = e.initialColor;			
		initialColor_rand_min = e.initialColor_rand_min;
		initialColor_rand_max = e.initialColor_rand_max;
		
		initialSize = e.initialSize;				
		initialSize_rand_min = e.initialSize_rand_min;
		initialSize_rand_max = e.initialSize_rand_max;

		texturePortionIndex = e.texturePortionIndex;
		numberOfTexturePortions = e.numberOfTexturePortions;

		currentState = e.currentState;

		reachDestinyAtAgeMin = e.reachDestinyAtAgeMin;
		reachDestinyAtAgeMax = e.reachDestinyAtAgeMax;
	}

	// destruktor
	virtual ~cEmitter()
	{
		for( size_t i = 0; i < particles.size(); i++ )
		{
			delete particles[i];
		}
	}

	// az összes részecske resetelése (használaton kívülre helyezése)
	virtual void ResetAllParticles()
	{
		for( size_t i = 0, s = particles.size(); i < s; i++ )
		{
			particles[i]->currentState = cParticle::UNUSED;
		}
	}

	// az emitter frissítése
	virtual void update(float dt) = 0;

	// az emitter részecskéinek kirajzolása
	virtual void Render() = 0;
};

#endif
