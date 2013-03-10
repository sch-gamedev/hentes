/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "playerlogiccomponent.h"
#include <SFML/Graphics.hpp>
#include "message.h"
#include "soundsystem.h"
#include "bulletmanager.h"
#include "collisiondescriptor.h"
#include "ingamestate.h"

PlayerLogicComponent::PlayerLogicComponent(GameObject *OwnerGameObject_in) :HumanoidLogicComponent(OwnerGameObject_in)
{
	framesLeftToShot = 0;
}
void PlayerLogicComponent::Update() 
{
	// J�t�kos ir�ny�t�sa:
	this->wantToMove = false;	
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
	{
		if (TryToJump())
		{
			SoundSystem::Instance()->FireSoundEvent("JUMP");
		}
	}

	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->wantToMove = true;		
		facingLeft = true;
	} 
	else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
	{
		this->wantToMove = true;		
		facingLeft = false;
	}
	//l�v�s a j�t�kossal
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		if ( sf::Keyboard::isKeyPressed(sf::Keyboard::J) ) 
		{
			if ( framesLeftToShot <= 0 ) {
				shotBullet(sf::Vector2f(24.f,0.f), 0, 0);
				framesLeftToShot = 16;

				SoundSystem::Instance()->FireSoundEvent("SHOOT");
			}
		}
		if ( sf::Keyboard::isKeyPressed(sf::Keyboard::K) ) 
		{	
			if ( framesLeftToShot <= 0 ) {
				for ( int i = 0; i<10; i++)
				shotBullet(sf::Vector2f(20.f,-10.f+(float)i*2), 0, 0);
				framesLeftToShot = 10;

				SoundSystem::Instance()->FireSoundEvent("SHOOT");
			}
		}

		
	}
	framesLeftToShot--;
	DefaultUpdate();
}

void PlayerLogicComponent::ReciveMessage(const Message &Message_in) 
{
	HumanoidLogicComponent::ReciveMessage(Message_in);
}


void PlayerLogicComponent::onDeath()
{
	// meghaltunk
	OwnerGameObject->GetInGameState()->PlayerDead();
}


void PlayerLogicComponent::SendDescriptor(GameObject* otherGO, sf::Vector2f collisionPoint)
{
	CollisionDescriptor desc;
	Message msg;
	msg.MessageType = COLLISION_DESCRIPTION_MESSAGE_TYPE;
	msg.CollisionDescriptionMessage.description = (void*)&desc;
	msg.CollisionDescriptionMessage.type = 0; // Default, a void* egy CollisionDescriptor oszt�lyra mutat.
	desc.activationLevel = 100;
	desc.dmg = 0.f;
	desc.hardness = 1;
	desc.collisionPoint = collisionPoint;
	otherGO->SendMessageToOtherComponents(msg);
}