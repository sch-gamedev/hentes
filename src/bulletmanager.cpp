/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "bulletmanager.h"

BulletManager::BulletManager() {
	this->DCM = nullptr;
	this->PCM = nullptr;
	this->LCM = nullptr;
	/*
	for ( int i = 0; i< 1000; i++ ) 
	{
		bullets.push_back(new Bullet());
	}
	*/
}

void BulletManager::setManagers(LogicComponentManager* LCM,PhysicsComponentManager* PCM,DrawableComponentManager* DCM)
{
	this->DCM = DCM;
	this->PCM = PCM;
	this->LCM = LCM;
}

void BulletManager::addBullet(sf::Vector2f position, sf::Vector2f velocityVertex, int bulletType, int lookType)
{
	int idx = bullets.size();

	bullets.push_back(new Bullet());

	shotBullet(idx, position, velocityVertex, bulletType, lookType);

	/*
	if ( DCM == nullptr || PCM == nullptr || LCM == nullptr) {
		#ifdef _DEBUG
		printf("BulletManager nem kapta meg a ComponentManager osztályokat.");
		#endif
		return;
	}
	int n = bullets.size();
	for ( unsigned i = (lastIndex + 1) % n; i != lastIndex; i = (i + 1) % n )
	{
		if ( !bullets[i]->inUse ) {
			shotBullet(i,position,velocityVertex,bulletType,lookType);
			lastIndex = i;
			return;
		}
	}
	for ( unsigned i=0; i<1000; i++)
	{
		bullets.push_back(new Bullet());
	}
	for ( unsigned i = (lastIndex + 1) % n; i != lastIndex; i = (i + 1) % n )
	{
		if ( !bullets[i]->inUse ) {
			shotBullet(i,position,velocityVertex,bulletType,lookType);
			lastIndex = i;
			return;
		}
	}
	#ifdef _DEBUG
	printf("BulletManager osztalyban valami nagyon el van baszva.");
	#endif
	return;
	*/
}

void  BulletManager::shotBullet(int index,sf::Vector2f position, sf::Vector2f velocityVertex, int bulletType, int lookType) 
{
	Bullet* bullet = bullets[index];
	bullet->bulletLogicComponent->setNewLogic(velocityVertex,bulletType);
	bullet->physicsComponent->setNewPosition(position);
	bullet->drawableComponent->JumpToScene(lookType);

	if (velocityVertex.x < 0.0f)
	{
		bullet->drawableComponent->SetFlippedHorizontally(true);
	}

	DCM->RegisterComponent(bullet->drawableComponent);
	LCM->RegisterComponent(bullet->bulletLogicComponent);
	PCM->RegisterComponent(bullet->physicsComponent);
	bullet->inUse = true;
}

void BulletManager::removeAllBullets()
{
	for( std::vector<Bullet*>::iterator it = bullets.begin(); it!= bullets.end(); ++it )
	{
		(*it)->RemoveIfUsed();
		delete *it;
	}

	bullets.clear();
}

// destruktor - a lefoglalt bullet objektumok felszabadítása
BulletManager::~BulletManager()
{
	removeAllBullets();
}
