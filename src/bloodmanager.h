/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _BLOOD_MANAGER_H_
#define _BLOOD_MANAGER_H_

#include <vector>
#include "blood.h"


/*****
Vér részecskerendszereket menedzselő osztály
*****/
class BloodManager
{
private :
	static const size_t INITIAL_NUM_OF_EMITTERS = 50;							// ennyi emitternek foglalunk helyet kezdetben a pool-ban
	static const size_t MAX_NUM_OF_EMITTERS = 100;								// maximum ennyi emitter lehet a játékban
	std::vector<cBloodEmitter *> emitters;										// vér emitterekre pointereket tároló dinamikus tömb

	// singleton pattern omg
	BloodManager();
	BloodManager(const BloodManager &c);
	BloodManager &operator=(const BloodManager &c);
	virtual ~BloodManager();


public :
	// példány lekérése
	static BloodManager &Instance()
	{
		static BloodManager bm;
		return bm;
	}

	// vér létrehozása a pályán
	void AddBlood(sf::Vector2f position, float lifetime, float spawningRate, float angleMin, float angleMax);

	// az összes véremitter resetelése (pálya betöltésekor pl)
	void ResetAllEmitters();

	// összes vér-emitter frissítése
	void UpdateEmitters(float dt);

	// vér emitterek frissítése
	void Render();
};

#endif
