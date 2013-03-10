/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "message.h"
#include "gameobject.h"

/*****
Különböző típusú komponensek absztrakt ősosztálya
*****/
class Component
{
protected:
	bool Deleted;																// az objektum meg van-e jelölve törlésre
	bool RemoveWithoutDeleting;

	//static unsigned int NextID;													// ha nem adunk manuálisan ID-t a komponensnek, akkor autoincrement kap egyet, ezt
	//unsigned int ID;															// a komponens egyedi azonosítója
	GameObject *OwnerGameObject;												// a komponenst tartalmazó objektum

public:
	// konstruktor
	Component(GameObject *OwnerGameObject_in) : OwnerGameObject(OwnerGameObject_in), Deleted(false), RemoveWithoutDeleting(false)
	{
	}

	// megjelölés törlésre
	void MarkAsDeleted(bool RemoveWithoutDeleting = false)
	{
		Deleted = true;
		this->RemoveWithoutDeleting = RemoveWithoutDeleting;
	}

	bool IsMarkedAsDeleted() 
	{
		return Deleted;
	}

	// üzenet fogadása
	virtual void ReciveMessage(const Message &Message_in) = 0;

	// komponens frissítése
	virtual void Update() = 0;


	bool ShouldRemoveWithoutDeleting()
	{
		return RemoveWithoutDeleting;
	}
};

#endif