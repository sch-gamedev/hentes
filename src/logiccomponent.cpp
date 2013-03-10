/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "logiccomponent.h"
#include "message.h"
/*****
üzenet fogadása
*****/
void LogicComponent::ReciveMessage(const Message &msg)
{
	if ( msg.MessageType == COLLIDED_WITH_OBJECT )
	{
		SendDescriptor(msg.CollidedWithObjectMessage.OtherGameObject, sf::Vector2f(msg.CollidedWithObjectMessage.x, msg.CollidedWithObjectMessage.y)); 
	}
}

/*****
komponens frissítése
*****/
void LogicComponent::Update()
{
}

void LogicComponent::SendDescriptor(GameObject* otherGO, sf::Vector2f collisionPoint)
{

}