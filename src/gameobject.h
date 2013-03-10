/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <list>
#include "message.h"

class Component;
class InGameState;

/*****
Játékbeli objektumok osztálya
*****/
class GameObject
{
private :
	InGameState* inGameState;
	static unsigned			NextID;												// a következő létrehozott GameObject-nek ez lesz az azonosítója
	unsigned				ID;													// az objektum egyedi azonosítója
	std::list<Component *>	Components;											// az objektumot alkotó komponensek
	bool Deleted;
	// megjelölés törlésre
public :
	//setOwner
	void setOwner(InGameState* inGameState) { this->inGameState = inGameState; }

	// konstruktor
	GameObject();

	// destruktor
	~GameObject();

	// üzenet küldése az összes tartalmazott komponensnek
	void SendMessageToOtherComponents(const Message &Message_in);

	void MarkAsDeleted();

	bool IsMarkedAsDeleted() 
	{
		return Deleted;
	}
	// komponens hozzáadása az objektumhoz
	void AddComponent(Component *Component_in)
	{
		Components.push_back(Component_in);
	}

	// InGameState lekérése
	InGameState* GetInGameState() { return inGameState; }
};

#endif
