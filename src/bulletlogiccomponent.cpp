/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "bulletlogiccomponent.h"
#include "bullet.h"
#include "collisiondescriptor.h"

void BulletLogicComponent::ReciveMessage(const Message &Message_in)
{
	switch (Message_in.MessageType)
	{
	case COLLIDED_WITH_OBJECT: 
		this->SendDescriptor(Message_in.CollidedWithObjectMessage.OtherGameObject, sf::Vector2f(Message_in.CollidedWithObjectMessage.x, Message_in.CollidedWithObjectMessage.y));
		break;
	case COLLISION_DESCRIPTION_MESSAGE_TYPE:
		if ( Message_in.CollisionDescriptionMessage.type == 0 && ((CollisionDescriptor*)Message_in.CollisionDescriptionMessage.description)->hardness > 0 ) this->ownerBullet->RemoveIfUsed();
		break;
	}
}

void BulletLogicComponent::Update()
{
	// el�bbut�bb meghal a l�ved�k
	if ( framesToLive <= 0 ) this->ownerBullet->RemoveIfUsed();
	framesToLive--;
	// a l�ved�k mozogni akar:
	Message msg;
	msg.MessageType = MOVEMENT_INTENT;
	msg.MovementIntentMessage.X = this->velocityVertex.x;
	msg.MovementIntentMessage.Y = this->velocityVertex.y;	
	OwnerGameObject->SendMessageToOtherComponents(msg);
}

void BulletLogicComponent::setNewLogic(sf::Vector2f velocityVertex,int bulletType)
{
	this->velocityVertex = velocityVertex;
	this->bulletType = bulletType;
	this->Deleted = false;
	this->framesToLive = 800;
	this->RemoveWithoutDeleting = true;
	this->stillLiving = true;
}

void BulletLogicComponent::SendDescriptor(GameObject* otherGO, sf::Vector2f collisionPoint) 
{
	CollisionDescriptor desc;
	Message msg;
	msg.MessageType = COLLISION_DESCRIPTION_MESSAGE_TYPE;
	msg.CollisionDescriptionMessage.description = (void*)&desc;
	msg.CollisionDescriptionMessage.type = 0; // Default, a void* egy CollisionDescriptor oszt�lyra mutat.
	desc.activationLevel = 50; 
	desc.dmg = 5.f;
	desc.hardness = 0;
	desc.collisionPoint = collisionPoint;
	otherGO->SendMessageToOtherComponents(msg);
}