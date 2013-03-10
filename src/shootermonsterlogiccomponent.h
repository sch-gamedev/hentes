/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _SHOOTERMONSTERLOGICCOMPONENT_H_
#define _SHOOTERMONSTERLOGICCOMPONENT_H_

#include "monsterlogiccomponent.h"
class ShooterMonsterLogicComponent : public MonsterLogicComponent 
{
private:
	int timeChangedFacing;
	int timeShootAgain;
	int timeToJump;
	int framesstillMoving;

public:
	ShooterMonsterLogicComponent(GameObject* owner, float health, float weaponId, float width, float height,PhysicsComponentManager* physicsComponentManager, PhysicsComponent* targetHitBox);
	// �zenet fogad�sa
	virtual void ReciveMessage(const Message &Message_in);

	// komponens friss�t�se
	virtual void Update();
};
#endif //_SHOOTERMONSTERLOGICCOMPONENT_H_