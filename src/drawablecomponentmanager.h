/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _DRAWABLECOMPONENTMANAGER_H_
#define _DRAWABLECOMPONENTMANAGER_H_

#include "componentmanager.h"
#include "drawablecomponent.h"

/*****
Megjeleníthető komponensek manager osztálya
*****/
class DrawableComponentManager : public ComponentManager<DrawableComponent>
{
public :
	// összes komponens frissítése
	virtual void Update();

	// összes komponens megjelenítése
	void Draw();
};

#endif
