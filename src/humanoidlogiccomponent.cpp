/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "humanoidligiccomponent.h"
#include "bulletmanager.h"
#include "collisiondescriptor.h"
#include "soundsystem.h"
#include "bloodmanager.h"

HumanoidLogicComponent::HumanoidLogicComponent( GameObject* owner ) :LogicComponent(owner)
{
	facingLeft= false;
	wantToMove= false;
	canJump = false;
	framesUntilNextJump = 0; // ne lehesen dupla jumpolni
	jumpStartingVelocity = 35.0f;
	moveSpeed = 10.0f;
	height = 128.0f;
	width = 64.0f;
	oldFacing = false;
	oldAnimation = -1;
	healtPoints = 100;
}


void HumanoidLogicComponent::ReciveMessage(const Message &Message_in)
{
	switch (Message_in.MessageType) {
	case COLLIDED_WITH_OBJECT:
		if ( Message_in.CollidedWithObjectMessage.Direction == Utility::BOTTOM )
		{
			canJump = true;
		}
		SendDescriptor(Message_in.CollidedWithObjectMessage.OtherGameObject, sf::Vector2f(Message_in.CollidedWithObjectMessage.x, Message_in.CollidedWithObjectMessage.y));
		break;
	case LOCATION_CHANGED:
		this->knownPosition.x = Message_in.LocationChangedMessage.Left;
		this->knownPosition.y = Message_in.LocationChangedMessage.Bottom;
		break;
	case COLLISION_DESCRIPTION_MESSAGE_TYPE:
		defaultCollisionHandling(Message_in);
		break;	
	}
}

void HumanoidLogicComponent::DefaultUpdate()
{
	Message msg;

	// halál ellenörzése:
	if ( healtPoints<= 0 ) onDeath();

	// Mozgás közlése a physicalComponentel
	if ( wantToMove ) 
	{
		if ( facingLeft)
		{
			msg.MessageType = MOVEMENT_INTENT;
			msg.MovementIntentMessage.X = -moveSpeed;
			msg.MovementIntentMessage.Y = 0.0;	
			OwnerGameObject->SendMessageToOtherComponents(msg);

		} 
		else
		{
			msg.MessageType = MOVEMENT_INTENT;
			msg.MovementIntentMessage.X = moveSpeed;
			msg.MovementIntentMessage.Y = 0.0;	
			OwnerGameObject->SendMessageToOtherComponents(msg);
		}
	}
	// animáció frissítése
	int animation;
	if ( this->mleeWeapon.isInProgress() )
	{
		animation = 3;
	}
	else if ( !this->canJump ) 
	{
		animation = 1;
	}
	else
	{
		if (wantToMove) 
		{
			animation = 2;
		}
		else
		{
			animation = 0;
		}
	}
	if ( animation != oldAnimation || oldFacing != facingLeft ) 
	{
		msg.MessageType = SET_ANIMATION_STATE_MESSAGE_TYPE;
		msg.SetAnimationStateMessage.animation = animation != oldAnimation ? animation : -1;
		msg.SetAnimationStateMessage.FlipHorizontal = facingLeft;
		OwnerGameObject->SendMessageToOtherComponents(msg);
		oldAnimation = animation;
		oldFacing = facingLeft;
	}
	framesUntilNextJump--;
	canJump = false;
}

void HumanoidLogicComponent::shotBullet(sf::Vector2f velocityVertex, int bulletType, int lookType)
{
	const float bullet_starting_distance = 30.f;
	const float bullet_width = 32.f;
	sf::Vector2f position = this->knownPosition + sf::Vector2f(0.f,height / 2.f);
	if ( facingLeft ) 
	{
		velocityVertex.x *= -1;
		position.x -= bullet_width + bullet_starting_distance;
	}
	else
	{
		position.x += width + bullet_starting_distance;
	}
	BulletManager::getInstance().addBullet(position,velocityVertex,0,0);
}

bool HumanoidLogicComponent::TryToJump()
{
	Message msg;
	if( canJump && framesUntilNextJump<=0) 
	{
		framesUntilNextJump = 3;
		msg.MessageType = JUMP_INTENT;
		msg.JumpIntentMessage.Power = jumpStartingVelocity;
		OwnerGameObject->SendMessageToOtherComponents(msg);

		/***** BloodManager használat demo ****
		***************************************
		Nagyon könnyű, az alábbi függvényt kell
		meghívni mindössze... Paraméterek:
		1. pozíció: az emitter helye world space-ben
		2. az emitter élettartama, tehát ennyi EZREDMÁSODPERCIG fogja nyomatni a vért
		3. az emitter intenzitása (új részecske/másodperc), célszerű kb 50 és 150 közé belőni
		4. és 5. ez a 2 paraméter határozza meg a kibocsátott részecskék irányát,
		előbbi a minimum utóbbi a maximum érték, és az x tengely pozitív feléhez képest
		bezárt szöget adják meg fokban
		***************************************/
		//BloodManager::Instance().AddBlood(sf::Vector2f(knownPosition.x + width / 2.f, knownPosition.y), 300, 100, 80, 100);

		return true;
	}

	return false;
}

void HumanoidLogicComponent::defaultCollisionHandling(const Message &Message_in)
{
	if ( Message_in.CollisionDescriptionMessage.type == 0 )
	{
		this->healtPoints -= ((CollisionDescriptor*)Message_in.CollisionDescriptionMessage.description)->dmg;
		if (((CollisionDescriptor*)Message_in.CollisionDescriptionMessage.description)->dmg > 0.0f)
		{
			sf::Vector2f collPt = ((CollisionDescriptor*)Message_in.CollisionDescriptionMessage.description)->collisionPoint;
			if (collPt.x < knownPosition.x + width)
			{
				BloodManager::Instance().AddBlood(collPt, 300, 100, -10, 10);
			}
			else
			{
				BloodManager::Instance().AddBlood(collPt, 300, 100, 170, 190);
			}
		}
	}
}


void HumanoidLogicComponent::SendDescriptor(GameObject* otherGO, sf::Vector2f collisionPoint)
{
	CollisionDescriptor desc;
	Message msg;
	msg.MessageType = COLLISION_DESCRIPTION_MESSAGE_TYPE;
	msg.CollisionDescriptionMessage.description = (void*)&desc;
	msg.CollisionDescriptionMessage.type = 0; // Default, a void* egy CollisionDescriptor osztályra mutat.
	desc.activationLevel = 90;
	desc.dmg = 0.f;
	desc.hardness = 1;
	desc.collisionPoint = collisionPoint;
	otherGO->SendMessageToOtherComponents(msg);
}