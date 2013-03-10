/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _PHYSICSCOMPONENT_H_
#define _PHYSICSCOMPONENT_H_

#include "component.h"
#include "message.h"
#include <SFML/System/Vector2.hpp>
class PhysicsComponentManager;


/*****
Fizikai komponensek osztálya. Minden komponens téglalap alakú
*****/
class PhysicsComponent : public Component
{
private: 
	bool Solid[4]; // Az egyes irányokból átjárható-e a téglalap
	bool Gravity; // Az adott objektumra hat-e a gravitáció
	sf::Vector2f LeftBottomCorner, OldLeftBottomCorner, Size; // A téglalap helye és mérete 	
	sf::Vector2f MovementIntent; // Mozgási szándékot jelez a PhysicalComponentManager felé. Miután az ezt feldolgazta, 0-ra visszaálítja.
	float FallingVelocity;
public :
	//PhysicsComponent létrehozása
	PhysicsComponent(GameObject *OwnerGameObject_in, sf::Vector2<float> LeftBottomCorner,sf::Vector2<float> Size, bool Gravity, bool Solid_Left,bool Solid_Top,bool Solid_Right,bool Solid_Bottom);
	PhysicsComponent(GameObject *OwnerGameObject_in, sf::Vector2<float> LeftBottomCorner,sf::Vector2<float> Size, bool Gravity, bool Solid);

	// pozíció lekérdezése - bal alsó sarok
	sf::Vector2f GetLeftBottomCorner() const { return LeftBottomCorner; }

	// pozíció lekérdezése - téglalap közepe
	sf::Vector2f GetCenterPosition() const { return LeftBottomCorner + (Size * 0.5f); }

	// méret lekérdezése
	sf::Vector2f GetSize() const { return Size; }

	// üzenet fogadása
	virtual void ReciveMessage(const Message & Message_in);
	
	// Ez a függvény segítségével értesítis a PhysicsComponentManager az ütközésről az osztályt
	virtual void Collide(PhysicsComponent* PhysicsComponent_in, Utility::DIRECTION Direction, sf::Vector2f collisionPoint); 

	// Ez a függvény segítségével értesítis a PhysicsComponentManager az osztályt az új heléyről
	virtual void LocationChanged(const sf::Vector2f NewLocation);

	// komponens frissítése
	virtual void Update();

	// Visszaadja a bal alsó sarok koordinátáját
	virtual sf::Vector2<float> GetLeftBottomCorner();

	// Visszaadja a komponens méretét	
	virtual sf::Vector2<float> GetSize();

	void setNewPosition(sf::Vector2f position);

	// A fizikai motor kezeli ezeket az objektumokat. A fizikai szimulációhoz a PhysicsComponentManagernek hozzá kell férnie az osztály leírásához.
	friend class PhysicsComponentManager;

};

#endif
