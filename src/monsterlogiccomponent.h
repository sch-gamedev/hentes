/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _MONSTERLOGICCOMPONENT_H_
#define _MONSTERLOGICCOMPONENT_H_

#include "humanoidligiccomponent.h"

class PhysicsComponent;
class PhysicsComponentManager;
class MonsterLogicComponent : public HumanoidLogicComponent
{
protected:
	// Innend fogjuk elk�rni a p�lya kin�zet�t, hogy tudja a sz�rny, merre ugr�ljon/l�j�n
	PhysicsComponentManager* physicsComponentManager;
	// A sz�rny c�lpontj�nak hitboxa
	PhysicsComponent* targetHitBox;
public:
	MonsterLogicComponent(GameObject* owner, float health, float dmg, float width, float height, PhysicsComponentManager* physicsComponentManager, PhysicsComponent* targetHitBox);
	virtual void onDeath();
};

#endif //_MONSTERLOGICCOMPONENT_H_
