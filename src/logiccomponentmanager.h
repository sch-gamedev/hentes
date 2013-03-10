/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _LOGICCOMPONENTMANAGER_H_
#define _LOGICCOMPONENTMANAGER_H_

#include "componentmanager.h"
#include "logiccomponent.h"

/*****
Logika komponensek manager osztálya
*****/
class LogicComponentManager : public ComponentManager<LogicComponent>
{
public :
	// összes komponens frissítése
	virtual void Update();
};

#endif
