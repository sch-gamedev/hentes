/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _WEAPONLOGICCOMPONENT_H_
#define _WEAPONLOGICCOMPONENT_H_

#include "logiccomponent.h"
class WeaponLogicComponent : public LogicComponent {
public:
	WeaponLogicComponent(GameObject* owner, int weaponId) :LogicComponent(owner) {}
	// �zenet fogad�sa
	virtual void ReciveMessage(const Message &Message_in) {}

	// komponens friss�t�se
	virtual void Update() {}

	virtual void SendDescriptor(GameObject* otherGO) {}
};
#endif //_WEAPONLOGICCOMPONENT_H_