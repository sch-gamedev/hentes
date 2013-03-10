/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <SFML/System/Vector2.hpp>
#include "utility.h"
class GameObject;
class PhysicsComponent;

/*****
Az egyes üzenettípusok felsorolása
*****/
enum MESSAGE_TYPE
{
	COLLIDED_WITH_OBJECT,
	LOCATION_CHANGED,
	MOVEMENT_INTENT,
	JUMP_INTENT,
	NUMBER_OF_MESSAGE_TYPES,
	SET_ANIMATION_STATE_MESSAGE_TYPE,
	COLLISION_DESCRIPTION_MESSAGE_TYPE
};


/*****
Ezzel az üzenettel szól a LogicComponent a LogicComponent osztálynak, hogy érintkezünk egy másik objektummal
*****/
struct CollidedWithObjectMessageType
{
	GameObject* OtherGameObject;	//Az objektum, amivel ütköztünk
	Utility::DIRECTION Direction;	// Melyik irányba helyezkedik el az object tőlünk
	float x, y;						// Ütkőzési pont
};

struct SetAnimationStateMessageType
{
	int animation; //Az objektum, amivel ütköztünk
	bool FlipHorizontal;
};

struct CollisionDescriptionMessageType
{
	int type; //milyen tipusu leírást adunk, mivel ez a game logic része, az engine-ben bármit adhatunk:
	void* description;
};
/*****
Ezzel az üzenettel szól a PhysicsComponent a LogicComponent és GraphicComponent osztályoknak, hogy megváltozott az objektum helye
*****/
struct LocationChangedMessageType
{
	float Left,Bottom;
};

/*****
Ezzel az üzenettel szól a LogicComponent a PhysicsComponentosztálynak, hogy megváltozott az objektum helye
*****/
struct JumpIntentMessageType
{
	float Power;
};

/*****
Ezzel az üzenettel szól a LogicComponent a PhysicsComponent osztálynak, hogy mozogni akar valamilyen irányba.
*****/
struct MovementIntentMessageType
{
	float X,Y; // A mozgás irányét és nagyságát ( Azaz a mozgás új helyét) leíró adatok
};

/*****
A komponensek által egymásnak küldött / egymástól fogadott
üzenetek típusa.
*****/
struct Message
{
	MESSAGE_TYPE MessageType;													// az adott üzenet típusa
	union																		// az összes üzenettípus felhasználása átlapolt memórián
	{
		CollidedWithObjectMessageType	CollidedWithObjectMessage;
		LocationChangedMessageType	LocationChangedMessage;
		MovementIntentMessageType	MovementIntentMessage;
		JumpIntentMessageType	JumpIntentMessage;
		SetAnimationStateMessageType SetAnimationStateMessage;
		CollisionDescriptionMessageType CollisionDescriptionMessage;
	};
};

#endif
