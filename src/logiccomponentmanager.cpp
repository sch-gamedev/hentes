/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "logiccomponentmanager.h"


void LogicComponentManager::Update() {
	RemoveMarkedComponents();
	for( std::list<LogicComponent*>::iterator it = Components.begin(); it != Components.end(); ++it) {
		(*it)->Update();
	}
}