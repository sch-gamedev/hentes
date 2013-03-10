/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _ENDLEVELLOGICCOMPONENT_H_
#define _ENDLEVELLOGICCOMPONENT_H_

#include "logiccomponent.h"
#include "collisiondescriptor.h"
#include "ingamestate.h"

class EndLevelLogicComponent : public LogicComponent {
public:
	EndLevelLogicComponent(GameObject* owner) :LogicComponent(owner) {}
	// �zenet fogad�sa
	virtual void ReciveMessage(const Message &Message_in)
	{
		switch( Message_in.MessageType )
		{
		case COLLISION_DESCRIPTION_MESSAGE_TYPE :
			{
				if ( Message_in.CollisionDescriptionMessage.type == 0 && ((CollisionDescriptor*)Message_in.CollisionDescriptionMessage.description)->activationLevel >= 100  )
				{
					// a j�t�kos nyert
					OwnerGameObject->GetInGameState()->LevelWon();
				}

				break;
			}
		
		}
	}

	// komponens friss�t�se
	virtual void Update() {}
};
#endif //_ENDLEVELLOGICCOMPONENT_H_
