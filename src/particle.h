/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <SFML/System.hpp>
#include "color.h"

// részecskék osztálya
class cParticle
{
public :
	size_t textureIndex;														// a részecskéhez felhasznált textúra indexe
	sf::Vector2f position;														// pozíció
	sf::Vector2f velocity;														// sebesség
	sf::Vector2f acceleration;													// gyorsulás
	float weight;																// tömeg
	float rotation;																// elforgatottság, fokban
	float lifetime;																// a részecske élettartama összesen, EZREDMÁSODPERCBEN
	float age;																	// a részecske kora EZREDMÁSODPERCBEN
	sColor4 color;																// a részecske színe
	float size;																	// a részecske mérete
	enum PARTICLE_STATE
	{
		UNUSED,																	// az ojjektum nincs használatban
		USED_DYNAMIC,															// a részecske használatban van
		USED_STATIC																// a részecske statikus
	};
	PARTICLE_STATE currentState;												// a részecske kurrens állapota
	enum DESTINY
	{
		DIE,
		BECOME_STATIC
	};
	DESTINY destiny;															// mi lesz a részecskével előbb-utóbb
	float reachDestinyAtAge;													// a részecske ennyi idős korában fejezi be a pályafutását mint dinamikus részecske
	unsigned short texturePortionIndex;											// ennyiedik részét jeleníti meg a textúrának
	unsigned short numberOfTexturePortions;										// ennyi darab részre osztottuk fel a textúrát


	// konstruktor
	cParticle(sf::Vector2f pos, sf::Vector2f vel, float weight, float rotation, float lifetime, sColor4 color, float size, size_t textureIndex, unsigned short texturePortionIndex, unsigned short numberOfTexturePortions, PARTICLE_STATE state, DESTINY destiny, float reachDestinyAtAge) : position(pos), velocity(vel), weight(weight), rotation(rotation), lifetime(lifetime), age(0), color(color), size(size), textureIndex(textureIndex), texturePortionIndex(texturePortionIndex), numberOfTexturePortions(numberOfTexturePortions), currentState(state), destiny(destiny), reachDestinyAtAge(reachDestinyAtAge)
	{
	}

	// update - a részecske mozgatása, animálása, miegyéb; paraméter a deltaTime és a részecskére ható erő
	virtual void update(float dt, const sf::Vector2f &force) = 0;

	// a részecske kirajzolása
	virtual void render();

	// ide került ez a segéd függvény, mert az SFML-ből kihagyták...SZEMETEK!
	static sf::Vector2f multiplyVector(const sf::Vector2f &vec, float f)
	{
		return sf::Vector2f(vec.x * f, vec.y * f);
	}
};

#endif
