/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _COLLISIONDESCRIPTOR_H_
#define _COLLISIONDESCRIPTOR_H_

struct CollisionDescriptor
{
	float dmg;  // ha az �tk�z�s sebzi a m�sik objektumot
	int hardness; // mennyire �thatolhat� az objektum ( pl. goly�: 0 , player, sz�rnyek : 1 , fal: 2 )
	int activationLevel; // mennyire reag�ljanak az �rint�s�re az objektumok ( player: 100, monster 90 )
	sf::Vector2f collisionPoint;
	Utility::DIRECTION direction;
	CollisionDescriptor()
	{
		dmg = 0.f;
		hardness = 0;
		activationLevel = 0;
	}
};

#endif