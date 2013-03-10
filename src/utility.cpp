/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "utility.h"

Utility::DIRECTION Utility::OpositeDirection(Utility::DIRECTION dir) {
		switch (dir) {
		case LEFT: return RIGHT;
		case RIGHT: return LEFT;
		case TOP: return BOTTOM;
		case BOTTOM: return TOP;
		default: return NONE;		
		}
	}