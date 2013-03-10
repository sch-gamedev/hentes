/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _HUMANOIDLOGICCOMPONENT_H_
#define _HUMANOIDLOGICCOMPONENT_H_

#include "logiccomponent.h"
#include "weapon.h"

// Ebből az osztályból származtatjuk a player és monster osztályokat
class HumanoidLogicComponent : public LogicComponent 
{
protected:
	//****************************
	//Egyébb statok
	//****************************
	float healtPoints;

	//****************************
	//lövéshez szükséges változók
	//****************************
	sf::Vector2f knownPosition;
	Weapon weapon;
	MleeWeapon mleeWeapon;

	//****************************
	//mozgáshoz szükséges változók
	//****************************

	//logika által álítandók
	bool facingLeft;
	bool wantToMove;
	bool canJump;
	int framesUntilNextJump; // ne lehesen dupla jumpolni

	float jumpStartingVelocity;
	float moveSpeed;
	float height;
	float width;



	//****************************
	//animációhoz szükséges változók
	//****************************
	bool oldFacing;
	int oldAnimation;

	//****************************
	//segédfügvények
	//****************************	
	
	//default construktór
	HumanoidLogicComponent( GameObject* owner );

	//default reakció az egyes üzenetekre
	void ReciveMessage(const Message &Message_in);

	//Megpróbál ugrani ( csak akkor ugrik, ha lehet )
	bool TryToJump();
	
	//Default update ( megpróbál mozogni, ugrani )
	void DefaultUpdate();

	//Lövést segítő függvény
	void shotBullet(sf::Vector2f velocityVertex, int bulletType, int lookType);

	//Ütközést feldolgozó függvény
	void defaultCollisionHandling(const Message &Message_in);

	// ha meghalt, akkor mi legyen ( ős dönti el )
	virtual void onDeath() = 0;

	virtual void SendDescriptor(GameObject* otherGO, sf::Vector2f collisionPoint);
};

#endif