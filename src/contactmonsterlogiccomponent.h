/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _CONTACTMONSTERLOGICCOMPONENT_H_
#define _CONTACTMONSTERLOGICCOMPONENT_H_

#include "MonsterLogicComponent.h"

class ContactMonsterLogicComponent : public MonsterLogicComponent 
{
private:
	double jumpheight;

public:
	ContactMonsterLogicComponent(GameObject* owner, float health, float dmg, float width, float height,PhysicsComponentManager* physicsComponentManager, PhysicsComponent* targetHitBox) :MonsterLogicComponent(owner,health,dmg,width,height,physicsComponentManager,targetHitBox) {
		
	}
	// �zenet fogad�sa
	virtual void ReciveMessage(const Message &Message_in) {}

	// komponens friss�t�se
	virtual void Update() {}
};

#endif //_CONTACTMONSTERLOGICCOMPONENT_H_