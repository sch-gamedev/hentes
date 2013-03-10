/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _PLAYERLOGICCOMPONENT_H_
#define _PLAYERLOGICCOMPONENT_H_

#include "humanoidligiccomponent.h"

class PlayerLogicComponent : public HumanoidLogicComponent {
private:
	sf::Vector2f SpawnPlace;
	int framesLeftToShot;
public:
	PlayerLogicComponent(GameObject *OwnerGameObject_in);
	virtual void Update();
	virtual void ReciveMessage(const Message &Message_in);
	virtual void onDeath();
	virtual void SendDescriptor(GameObject* otherGO, sf::Vector2f collisionPoint);
};

#endif //_PLAYERLOGICCOMPONENT_H_