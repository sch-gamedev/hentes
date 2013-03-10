/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "shootermonsterlogiccomponent.h"
#include "bulletmanager.h"
#include "collisiondescriptor.h"
ShooterMonsterLogicComponent::ShooterMonsterLogicComponent(GameObject* owner, float health, float weaponId, float width, float height,PhysicsComponentManager* physicsComponentManager, PhysicsComponent* targetHitBox) :MonsterLogicComponent(owner,health,weaponId,width,height,physicsComponentManager,targetHitBox)
{
	timeChangedFacing = 0;
	timeShootAgain = 0;
	timeToJump = 0;
}

void ShooterMonsterLogicComponent::ReciveMessage(const Message &Message_in) 
{
	HumanoidLogicComponent::ReciveMessage(Message_in);
}

void ShooterMonsterLogicComponent::Update() 
{
	const int framestoMove = 50;
	wantToMove = false;
	//Message msg;
	if ( timeShootAgain < 0 )
	{
		shotBullet(sf::Vector2f(18.f,0.f),0,0);
		timeShootAgain = 25;
	}
	if ( timeToJump < 0 && canJump)
	{
		TryToJump();
		timeToJump = 80;
	}
	if ( timeChangedFacing < 0) {
		framesstillMoving = framestoMove;
		timeChangedFacing = 90;
		facingLeft = !facingLeft;
	}
	if ( framesstillMoving > 0 )
	{
		wantToMove = true;	
	}
	timeChangedFacing--;
	timeShootAgain--;
	timeToJump--;
	framesstillMoving--;
	HumanoidLogicComponent::DefaultUpdate();
}
