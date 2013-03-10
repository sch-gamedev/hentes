/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "monsterlogiccomponent.h"
#include "physicscomponent.h"
#include "physicscomponentmanager.h"
MonsterLogicComponent::MonsterLogicComponent(GameObject* owner, float health, float dmg, float width, float height, PhysicsComponentManager* physicsComponentManager, PhysicsComponent* targetHitBox) :HumanoidLogicComponent(owner)
{
		this->physicsComponentManager = physicsComponentManager;
		this->targetHitBox = targetHitBox;
}


void MonsterLogicComponent::onDeath()
{
	this->OwnerGameObject->MarkAsDeleted();
}