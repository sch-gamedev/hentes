/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _AMMOLOGICCOMPONENT_H_
#define _AMMOLOGICCOMPONENT_H_

#include "logiccomponent.h"

class AmmoLogicComponent : public LogicComponent {

public:

	AmmoLogicComponent(GameObject *OwnerGameObject_in,int WeaponID,int Amount);

	// �zenet fogad�sa
	virtual void ReciveMessage(const Message &Message_in);

	// komponens friss�t�se
	virtual void Update();

	virtual void SendDescriptor(GameObject* otherGO) {}
};

#endif //_AMMOLOGICCOMPONENT_H_