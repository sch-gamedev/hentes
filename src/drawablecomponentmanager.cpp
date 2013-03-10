/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "drawablecomponentmanager.h"


void DrawableComponentManager::Update() 	
{
	RemoveMarkedComponents();
	for( std::list<DrawableComponent*>::iterator i = Components.begin(); i != Components.end(); i++ )
	{
		(*i)->Update();
	}
}


void DrawableComponentManager::Draw() 
{
	for( std::list<DrawableComponent*>::iterator i = Components.begin(); i != Components.end(); i++ )
	{
		(*i)->Draw();
	}
}