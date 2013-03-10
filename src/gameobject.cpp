/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "gameobject.h"
#include "component.h"

// statikus adattagok
unsigned GameObject::NextID = 0;

/*****
Konstruktor
*****/
GameObject::GameObject()
{
	// egyedi azonosító "generálása"
	ID = NextID++;
	Deleted = false;
}

/*****
Destruktor
*****/
GameObject::~GameObject()
{
}

/*****
Üzenet küldése az összes tartalmazott komponensnek.
Így valósítható meg a komponensek közötti kommunikáció.
*****/
void GameObject::SendMessageToOtherComponents(const Message &Message_in)
{
	// üzenet küldése az összes komponensnek
	for( std::list<Component *>::iterator i = Components.begin(); i != Components.end(); i++ )
	{
		(*i)->ReciveMessage(Message_in);
	}
}


void GameObject::MarkAsDeleted() 
{
	Deleted = true;
	for (std::list<Component*>::iterator it = Components.begin(); it!= Components.end(); ++it) (*it)->MarkAsDeleted();
}