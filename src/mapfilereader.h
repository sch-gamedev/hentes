/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _MAFILEREADER_H_
#define _MAFILEREADER_H_
#include "configfilereaderbase.hpp"
#include "gameobject.h"
#include "drawablecomponentmanager.h"
#include "physicscomponentmanager.h"
#include "logiccomponentmanager.h"


class MapFileReader : public ConfigFileReaderBase<GameObject*> {
private:
	DrawableComponentManager  *DCM;												// megjeleníthető komponensek menedzsere
	PhysicsComponentManager	  *PCM;												// fizikai komponensek menedzsere
	LogicComponentManager	  *LCM;

	PhysicsComponent		  *PlayerPhysicsComponent;							// !!! DO NOT EVER TOUCH THIS !!!
	size_t					  BackgroundTextureIndex;							// !!! DO NOT EVER TOUCH THIS EITHER !!!

protected:
	virtual GameObject* ParseRecord(std::string str);
	virtual GameObject* GetSpawnPlaceObject(std::string& s);
	virtual GameObject* GetPlatformObject(std::string& s);
	virtual GameObject* GetWeaponObject(std::string& s);
	virtual GameObject* GetAmmoObject(std::string& s);
	virtual GameObject* GetMonsterObject(std::string& s);
	virtual GameObject* GetEndLevelButtonObject(std::string& s);
	virtual GameObject* GetSpriteObject(std::string& s);
	virtual void GetBackgroundTexture(std::string &s);
public:
	MapFileReader( 	DrawableComponentManager  *DCM, PhysicsComponentManager	*PCM, LogicComponentManager	*LCM);

	PhysicsComponent *GetPlayerPhysicsComponent()
	{
		return PlayerPhysicsComponent;
	}

	size_t GetBackgroundTextureIndex()
	{
		return BackgroundTextureIndex;
	}
};

#endif //_MAFILEREADER_H_