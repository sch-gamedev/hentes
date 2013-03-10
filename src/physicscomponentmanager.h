/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _PHYSICSCOMPONENTMANAGER_H_
#define _PHYSICSCOMPONENTMANAGER_H_

#include "componentmanager.h"
#include "physicscomponent.h"
#include <vector>

/*****
Fizikai komponensek manager osztálya
*****/

class PhysicsComponentManager : public ComponentManager<PhysicsComponent>
{
private:
	const float GravityPower;

	struct QueuedMessage 
	{ 
		QueuedMessage(PhysicsComponent* a, PhysicsComponent* b, Utility::DIRECTION Direction, sf::Vector2f collPt);

		PhysicsComponent*	Component1;		// ütközésben résztvevő egyik komponens
		PhysicsComponent*	Component2;		// ütközésben résztvevő másik komponens
		Utility::DIRECTION	Direction;		// ütközési irány
		sf::Vector2f		collisionPoint;	// ütközési pont, VÉR miatt bevezetve

		bool operator==(const QueuedMessage& QueuedMessage_in); 
	};

	std::vector<QueuedMessage> QueuedMessages;

public :

	PhysicsComponentManager() :GravityPower(2.0f) { }

	// összes komponens frissítése
	virtual void Update();

	// feldolgozandó ütközést ad az ütközéslistához
	void addQueuedMessage(QueuedMessage Msg);

	// Ez az AI-nak kell, hogy tudjon a játékos felé haladni, a játékost támadni, a játékoshoz ugrálni 
	std::list<PhysicsComponent* >* getPhysicsComponents() 
	{
		return &(this->Components);
	}
};

#endif
