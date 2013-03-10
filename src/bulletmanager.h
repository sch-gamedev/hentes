/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_
#include <vector>
#include "bullet.h"
#include "physicscomponentmanager.h"
#include "logiccomponentmanager.h"
#include "drawablecomponentmanager.h"

class BulletManager 
{
private:
	// A felhaszn�lhat� t�lt�nyek
	std::vector<Bullet*> bullets;
	BulletManager();
	BulletManager(BulletManager& b);
	BulletManager& operator=(const BulletManager& b);
	~BulletManager();
	LogicComponentManager* LCM;
	PhysicsComponentManager* PCM;
	DrawableComponentManager* DCM;
	int lastIndex;
	void shotBullet(int index,sf::Vector2f position, sf::Vector2f velocityVertex, int bulletType, int lookType);
public:
	static BulletManager &getInstance() 
	{
		static BulletManager instance;
		return instance;
	}
	void setManagers(LogicComponentManager* LCM,PhysicsComponentManager* PCM,DrawableComponentManager* DCM);
	void addBullet(sf::Vector2f position, sf::Vector2f velocityVertex, int bulletType, int lookType);
	void removeAllBullets();
};
#endif //_BULLETMANAGER_H_