/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _WEAPON_H_
#define _WEAPON_H_

class Weapon
{
public:
	Weapon() {}
	void useWeapon() {}
};

class MleeWeapon
{
public:
	MleeWeapon() {}
	void useWeapon() {}
	bool isInProgress() { return false; }
};
#endif //_WEAPON_H_
