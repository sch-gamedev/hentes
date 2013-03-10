/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "physicscomponent.h"
/*****
PhysicsComponent létrehozása
*****/
PhysicsComponent::PhysicsComponent(GameObject *OwnerGameObject_in, sf::Vector2<float> LeftBottomCorner,sf::Vector2<float> Size, bool Gravity, bool Solid_Left,bool Solid_Top,bool Solid_Right,bool Solid_Bottom) : Component(OwnerGameObject_in)
{
	this->LeftBottomCorner = LeftBottomCorner;
	this->Size = Size;
	this->Gravity = Gravity;
	this->Solid[Utility::LEFT] = Solid_Left;
	this->Solid[Utility::TOP] = Solid_Top;
	this->Solid[Utility::RIGHT] = Solid_Right;
	this->Solid[Utility::BOTTOM] = Solid_Bottom;
	this->FallingVelocity = 0.0f;
}

/*****
PhysicsComponent létrehozása ugyanolyan tulajdonságú oldalakkal 
*****/
PhysicsComponent::PhysicsComponent(GameObject *OwnerGameObject_in, sf::Vector2<float> LeftBottomCorner,sf::Vector2<float> Size, bool Gravity, bool Solid) :Component(OwnerGameObject_in)
{
	this->LeftBottomCorner = LeftBottomCorner;
	this->Size = Size;
	this->Gravity = Gravity;
	this->Solid[Utility::LEFT] = Solid;
	this->Solid[Utility::TOP] = Solid;
	this->Solid[Utility::RIGHT] = Solid;
	this->Solid[Utility::BOTTOM] = Solid;
	this->FallingVelocity = 0.0f;	
}

/*****
üzenet fogadása
*****/
void PhysicsComponent::ReciveMessage(const Message &Message_in)
{
	switch ( Message_in.MessageType ) {
	case MOVEMENT_INTENT:
		//Eltároljuk, hogy merre szeretnénk mozogni. Ezt majd a PhysicalComponentManager használja
		this->MovementIntent.x = Message_in.MovementIntentMessage.X;
		this->MovementIntent.y = Message_in.MovementIntentMessage.Y;
		break;
	case JUMP_INTENT:
		this->FallingVelocity+= Message_in.JumpIntentMessage.Power;
		break;
	default:
		break;
	}
}

/*****
Ez a függvény segítségével értesítis a PhysicsComponentManager az ütközésről az osztályt
*****/
void PhysicsComponent::Collide(PhysicsComponent* PhysicsComponent_in, Utility::DIRECTION Direction, sf::Vector2f collisionPoint) {
	Message msg;

	msg.MessageType = COLLIDED_WITH_OBJECT;
	msg.CollidedWithObjectMessage.OtherGameObject = PhysicsComponent_in->OwnerGameObject; //Az objektum, amivel ütköztünk
	msg.CollidedWithObjectMessage.Direction = Direction;
	msg.CollidedWithObjectMessage.x = collisionPoint.x;
	msg.CollidedWithObjectMessage.y = collisionPoint.y;

	//Szólunk, hogy kezelendő ütközés van (Erre az üzenetre a valószínüleg a LogicComponent reagál).
	OwnerGameObject->SendMessageToOtherComponents(msg);
}

/*****
Ez a függvény segítségével értesítis a PhysicsComponentManager az osztályt az új heléyről
*****/
void PhysicsComponent::LocationChanged(const sf::Vector2f NewLocation) {
	Message msg;
	this->OldLeftBottomCorner = this->LeftBottomCorner;
	this->LeftBottomCorner = NewLocation;
	msg.MessageType = LOCATION_CHANGED;
	msg.LocationChangedMessage.Bottom = NewLocation.y;
	msg.LocationChangedMessage.Left = NewLocation.x;
	OwnerGameObject->SendMessageToOtherComponents(msg);
}

/*****
komponens frissítése
Ez a függvény nem csinál semmit, tervezési hiba miatt kellett megcsinálni XD
*****/
void PhysicsComponent::Update()
{
	//Ez a függvény nem csinál semmit, tervezési hiba miatt kellett megcsinálni XD
}


/*****
Visszaadja a bal alsó sarok koordinátáját
*****/
sf::Vector2<float> PhysicsComponent::GetLeftBottomCorner() {
	return this->LeftBottomCorner;
}

/*****
Visszaadja a komponens méretét	
*****/
sf::Vector2<float> PhysicsComponent::GetSize() {
	return this->Size;
}


void PhysicsComponent::setNewPosition(sf::Vector2f position) 
{
	this->FallingVelocity = 0;
	this->LeftBottomCorner = position;
	this->MovementIntent = sf::Vector2f();
	this->OldLeftBottomCorner = position;
}