/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _BULLETLOGICCOMPONENT_H_
#define _BULLETLOGICCOMPONENT_H_
#include "logiccomponent.h"

class Bullet;
class BulletLogicComponent : public LogicComponent
{
private:
	sf::Vector2f velocityVertex;
	int bulletType;
	Bullet* ownerBullet;
	int framesToLive;
	bool stillLiving;
public:
	BulletLogicComponent(GameObject *OwnerGameObject_in, Bullet* ownerBullet) :LogicComponent(OwnerGameObject_in),ownerBullet(ownerBullet) { }
	// új löszert lövünk ki és felhasználjuk a már meglévő logic componentet.
	void setNewLogic(sf::Vector2f velocityVertex,int bulletType);
	
	// üzenet fogadása
	virtual void ReciveMessage(const Message &Message_in);

	// komponens frissítése
	virtual void Update();

	virtual void SendDescriptor(GameObject* otherGO, sf::Vector2f collisionPoint);
};

#endif //_BULLETLOGICCOMPONENT_H_