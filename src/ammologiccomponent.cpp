/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "ammologiccomponent.h"

AmmoLogicComponent::AmmoLogicComponent(GameObject *OwnerGameObject_in,int WeaponID,int Amount) :LogicComponent(OwnerGameObject_in)
{

}

// �zenet fogad�sa
void AmmoLogicComponent::ReciveMessage(const Message &Message_in) 
{
	if ( Message_in.MessageType == COLLIDED_WITH_OBJECT) {
		OwnerGameObject->MarkAsDeleted();
	}
}

// komponens friss�t�se
void AmmoLogicComponent::Update()
{
}