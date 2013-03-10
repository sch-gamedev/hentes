/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _LOGICCOMPONENT_H_
#define _LOGICCOMPONENT_H_

#include "component.h"


/*****
Logika komponensek osztálya
*****/
class LogicComponent : public Component
{
public :
	// konstruktor
	LogicComponent(GameObject *OwnerGameObject_in) : Component(OwnerGameObject_in)
	{
	}

	// üzenet fogadása
	virtual void ReciveMessage(const Message &Message_in);

	// komponens frissítése
	virtual void Update();

	// komponenst leírást ad az őt reprezentáló objektumról az ütközés 
	virtual void SendDescriptor(GameObject* otherGO, sf::Vector2f collisionPoint);
};

#endif
