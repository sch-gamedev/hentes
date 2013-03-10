/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _BULLET_H_
#define _BULLET_H_
#include "physicscomponent.h"
#include "bulletlogiccomponent.h"
#include "drawablecomponent.h"

class BulletManager;
class Bullet
{
private:
	PhysicsComponent* physicsComponent;
	BulletLogicComponent* bulletLogicComponent;
	DrawableComponent* drawableComponent;
	GameObject* gameObject;
	bool inUse;
public:
	Bullet();
	~Bullet();
	void RemoveIfUsed();
	friend class BulletManager;
};
#endif //_BULLET_H_