/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _PLATFORMLOGICCOMPONENT_H_
#define _PLATFORMLOGICCOMPONENT_H_

#include "logiccomponent.h"
class PlatformLogicComponent : public LogicComponent
{
private:

public:
	PlatformLogicComponent(GameObject* owner) :LogicComponent(owner) {}
	virtual void SendDescriptor(GameObject* otherGO)
	{
		CollisionDescriptor desc;
		Message msg;
		msg.MessageType = COLLISION_DESCRIPTION_MESSAGE_TYPE;
		msg.CollisionDescriptionMessage.description = (void*)&desc;
		msg.CollisionDescriptionMessage.type = 0; // Default, a void* egy CollisionDescriptor oszt�lyra mutat.
		desc.hardness = 2;
		otherGO->SendMessageToOtherComponents(msg);
	}
};

#endif //_PLATFORMLOGICCOMPONENT_H_