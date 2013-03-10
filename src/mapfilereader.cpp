/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "mapfilereader.h"
#include <sstream>
#include "playerlogiccomponent.h"
#include "texturemanager.h"
#include "ammologiccomponent.h"
#include "weaponlogiccomponent.h"
#include "endlevellogiccomponent.h"
#include "shootermonsterlogiccomponent.h"
#include "contactmonsterlogiccomponent.h"
#include "spriteconfigmanager.h"
#include "platformlogiccomponent.h"

struct TypeBuilderKey {
	std::string mainType;
	GameObject* (*typeBuilder)(std::string& s);
};

void MapFileReader::GetBackgroundTexture(std::string &s)
{
	char dummy[100];
	char texture_name[100];
	if ( sscanf(s.c_str(),"%s%s",dummy,texture_name) != 2 )
	{
#ifdef _DEBUG
		printf("> ERROR! cannot load background texture: %s\n", s.c_str());
#endif
		return;
	}

	std::string texture_path = "Content/Sprites/";
	texture_path.append(texture_name);
	if( TextureManager::Instance().LoadTexture(texture_path, BackgroundTextureIndex) )
	{
#ifdef _DEBUG
		printf("> ERROR! cannot load background texture!\n");
#endif
	}
}

GameObject* MapFileReader::GetSpawnPlaceObject(std::string& s) 
{
	char dummy[100];
	float x, y;
	if ( sscanf(s.c_str(),"%s%f%f",dummy,&x,&y) != 3 ) return 0;
	GameObject* obj = new GameObject();
	// DrawableComponent
	DrawableComponent * dc = new DrawableComponent(obj);
	SpriteConfig sc = SpriteConfigManager::Instance()->LookupSpriteConfig("PLAYER_DEFAULT_SPRITE_ID");
	dc->Set(64.f, 128.f, sf::Vector2f(x, y), sc.textureId, DrawableComponent::WORLD_SPACE);
	dc->CreateAnimatedSprite(sc.rows, sc.columns, sc.duration, sc.action);
	for( unsigned i=0; i<sc.rows; i++)	
	{
		dc->AccessScene(i)->SetOnFinish(Scene::REPEAT_SCENE);
	}
	obj->AddComponent(dc);
	DCM->RegisterComponent(dc);
	//PhysicsComponent hozzáadása
	PhysicsComponent* pc = new PhysicsComponent(obj,sf::Vector2f(x,y),sf::Vector2f(64.0f, 128.0f),true,true);
	obj->AddComponent(pc);
	PCM->RegisterComponent(pc);


	PlayerPhysicsComponent = pc;

	//PlayerLogic Hozzáadása
	PlayerLogicComponent* plc = new PlayerLogicComponent(obj);
	obj->AddComponent(plc);
	LCM->RegisterComponent(plc);
	return obj;
}

GameObject* MapFileReader::GetPlatformObject(std::string& s)
{
	char dummy[100];
	char spriteID[100];
	float x, y, width, height, sprite_X,sprite_Y,sprite_Width,sprite_Height;
	int solidLeft,solidTop,solidRight,solidBottom;
	if ( sscanf(s.c_str(),"%s%f%f%f%f%d%d%d%d%s%f%f%f%f",dummy,&x,&y,&width,&height,&solidLeft,&solidTop,&solidRight,&solidBottom,spriteID,&sprite_X,&sprite_Y,&sprite_Width,&sprite_Height) != 14 ) return 0;
	GameObject* obj = new GameObject();
	//Drawable Component hozzáadása
	DrawableComponent * dc = new DrawableComponent(obj);
	SpriteConfig sc = SpriteConfigManager::Instance()->LookupSpriteConfig(spriteID);
	dc->Set(width, height, sf::Vector2f(x, y), sc.textureId, DrawableComponent::WORLD_SPACE);
	dc->CreateAnimatedSprite(sc.rows, sc.columns, sc.duration, sc.action);
	obj->AddComponent(dc);
	DCM->RegisterComponent(dc);
	
	//PanelLogicComponent Hozzáadása
	LogicComponent* lc = new PlatformLogicComponent(obj);
	obj->AddComponent(lc);
	LCM->RegisterComponent(lc);

	PhysicsComponent* pc = new PhysicsComponent(obj,sf::Vector2f(x,y),sf::Vector2f(width,height),false, solidLeft == 1 ,solidTop == 1,solidRight == 1, solidBottom == 1);
	obj->AddComponent(pc);
	PCM->RegisterComponent(pc);	
	return obj;
}

GameObject* MapFileReader::GetWeaponObject(std::string& s)
{
	char dummy[100];
	float x, y;
	int weaponID;
	if ( sscanf(s.c_str(),"%s%f%f%d",dummy,&x,&y,&weaponID) != 4 ) return 0;
	GameObject* obj = new GameObject();
	//Drawable Component hozzáadása
	/*
		size_t texture_id;
		int err = TextureManager::Instance().LoadTexture("fw.png", texture_id);
		DrawableComponent * dc = new DrawableComponent(obj);
		dc->Set(64, 64, sf::Vector2f(x, y), texture_id, DrawableComponent::WORLD_SPACE);
		dc->CreateAnimatedSprite(4, 8, 500, Scene::NEXT_SCENE);
		obj->AddComponent(dc);
		DCM->RegisterComponent(dc);
	*/
	DrawableComponent * dc = new DrawableComponent(obj);
	SpriteConfig sc = SpriteConfigManager::Instance()->LookupSpriteConfig("WEAPON_SPRITE_ID");
	dc->Set(256.f, 64.f, sf::Vector2f(x, y), sc.textureId, DrawableComponent::WORLD_SPACE);
	dc->CreateAnimatedSprite(sc.rows, sc.columns, sc.duration, sc.action);
	obj->AddComponent(dc);
	DCM->RegisterComponent(dc);
	
	//PhysicsComponent hozzáadása
	PhysicsComponent* pc = new PhysicsComponent(obj,sf::Vector2f(x,y),sf::Vector2f(256,64),false,false);
	obj->AddComponent(pc);
	PCM->RegisterComponent(pc);	
	//AmmoLogic Hozzáadása
	LogicComponent* lc = new WeaponLogicComponent(obj,weaponID);
	obj->AddComponent(lc);
	LCM->RegisterComponent(lc);
	return obj;
}

GameObject* MapFileReader::GetAmmoObject(std::string& s)
{
	char dummy[100];
	float x, y;
	int weaponID,amount;
	if ( sscanf(s.c_str(),"%s%f%f%d%d",dummy,&x,&y,&weaponID,&amount) != 5 ) return 0;
	GameObject* obj = new GameObject();
	//Drawable Component hozzáadása
	DrawableComponent * dc = new DrawableComponent(obj);
	SpriteConfig sc = SpriteConfigManager::Instance()->LookupSpriteConfig("AMMO_SPRITE_ID");
	dc->Set(64.f, 64.f, sf::Vector2f(x, y), sc.textureId, DrawableComponent::WORLD_SPACE);
	dc->CreateAnimatedSprite(sc.rows, sc.columns, sc.duration, sc.action);
	obj->AddComponent(dc);
	DCM->RegisterComponent(dc);

	//PhysicsComponent hozzáadása
	PhysicsComponent* pc = new PhysicsComponent(obj,sf::Vector2f(x,y),sf::Vector2f(64.f,64.f),false,false);
	obj->AddComponent(pc);
	PCM->RegisterComponent(pc);	
	//AmmoLogic Hozzáadása
	LogicComponent* lc = new AmmoLogicComponent(obj,weaponID,amount);
	obj->AddComponent(lc);
	LCM->RegisterComponent(lc);
	return obj;

}
GameObject* MapFileReader::GetMonsterObject(std::string& s)
{
	char dummy[100];
	char type[100];
	char spriteId[100];
	float x,y,width,height,health, damage_weaponid;
	if ( sscanf(s.c_str(),"%s%f%f%f%f%s%s%f%f",dummy,&x,&y,&width,&height,type,spriteId,&health, &damage_weaponid) != 9 ) return 0;
	GameObject* obj = new GameObject();
	//Drawable Component hozzáadása
	DrawableComponent * dc = new DrawableComponent(obj);
	SpriteConfig sc = SpriteConfigManager::Instance()->LookupSpriteConfig(spriteId);
	dc->Set(width, height, sf::Vector2f(x, y), sc.textureId, DrawableComponent::WORLD_SPACE);
	dc->CreateAnimatedSprite(sc.rows, sc.columns, sc.duration, sc.action);
	for( unsigned i=0; i<sc.rows; i++)	
	{
		dc->AccessScene(i)->SetOnFinish(Scene::REPEAT_SCENE);
	}
	obj->AddComponent(dc);
	DCM->RegisterComponent(dc);
	
	//PhysicsComponent hozzáadása
	PhysicsComponent* pc = new PhysicsComponent(obj,sf::Vector2f(x,y),sf::Vector2f(width,height),true,true);
	obj->AddComponent(pc);
	PCM->RegisterComponent(pc);	
	//AmmoLogic Hozzáadása
	LogicComponent* lc;
	if ( !strcmp(type,"SHOOTER")) 
	{
		lc	= new ShooterMonsterLogicComponent(obj,health,damage_weaponid,width,height, PCM, nullptr);
	}
	else
	{
		lc = new ContactMonsterLogicComponent(obj,health,damage_weaponid,width,height, PCM, nullptr);
	}
	obj->AddComponent(lc);
	LCM->RegisterComponent(lc);
	return obj;
}

GameObject* MapFileReader::GetEndLevelButtonObject(std::string& s)
{
	char dummy[100];
	float x,y;
	if ( sscanf(s.c_str(),"%s%f%f",dummy,&x,&y) != 3 ) return 0;
	GameObject* obj = new GameObject();
	//Drawable Component hozzáadása
	/*
		size_t texture_id;
		int err = TextureManager::Instance().LoadTexture("lena.png", texture_id);
		DrawableComponent * dc = new DrawableComponent(obj);
		dc->Set(64, 64, sf::Vector2f(x, y), texture_id, DrawableComponent::WORLD_SPACE);
		dc->CreateAnimatedSprite(4, 8, 500, Scene::NEXT_SCENE);
		obj->AddComponent(dc);
		DCM->RegisterComponent(dc);
	*/
	DrawableComponent * dc = new DrawableComponent(obj);
	SpriteConfig sc = SpriteConfigManager::Instance()->LookupSpriteConfig("ENDLEVEL_SPRITE_ID");
	dc->Set(256.f, 128.f, sf::Vector2f(x, y), sc.textureId, DrawableComponent::WORLD_SPACE);
	dc->CreateAnimatedSprite(sc.rows, sc.columns, sc.duration, sc.action);
	obj->AddComponent(dc);
	DCM->RegisterComponent(dc);

	//PhysicsComponent hozzáadása
	PhysicsComponent* pc = new PhysicsComponent(obj,sf::Vector2f(x,y),sf::Vector2f(256.f, 128.f),false,false);
	obj->AddComponent(pc);
	PCM->RegisterComponent(pc);	
	//AmmoLogic Hozzáadása
	LogicComponent* lc = new EndLevelLogicComponent(obj);
	obj->AddComponent(lc);
	LCM->RegisterComponent(lc);
	return obj;
}

GameObject* MapFileReader::GetSpriteObject(std::string& s)
{
	char dummy[100];
	char type[100];
	char spriteId[200];
	float x,y,width,height;
	if ( sscanf(s.c_str(),"%s%s%f%f%s%f%f",dummy,spriteId,&x,&y,type,&width,&height) != 7 )
	{
#ifdef _DEBUG
		printf("> ERROR! MapFileReader::GetSpriteObject - parsing failed!\n");
#endif
		return nullptr;
	}
	GameObject *obj = new GameObject();
	//csak drawable component van
	DrawableComponent *dc = new DrawableComponent(obj);
	SpriteConfig sc = SpriteConfigManager::Instance()->LookupSpriteConfig(spriteId);

	DrawableComponent::COORDINATE_SPACE coord_space;
	if( strcmp(type, "SCREEN_SPACE") == 0 )
	{
		coord_space = DrawableComponent::SCREEN_SPACE;
	}
	else if( strcmp(type, "WORLD_SPACE") == 0 )
	{
		coord_space = DrawableComponent::WORLD_SPACE;
	}
	else
	{
#ifdef _DEBUG
		printf("> ERROR! MapFileReader::GetSpriteObject - invalid coordinate space '%s'\n", type);
#endif
	}

	dc->Set(width, height, sf::Vector2f(x, y), sc.textureId, coord_space);
	dc->CreateAnimatedSprite(sc.rows, sc.columns, sc.duration, sc.action);

	obj->AddComponent(dc);
	DCM->RegisterComponent(dc);
	return obj;
}

GameObject* MapFileReader::ParseRecord(std::string str) 
{
	std::istringstream iss(str);
    std::string mainType;
    iss >> mainType;
	
	if( mainType == "SPAWNPLACE" )
		return GetSpawnPlaceObject(str);
	else if(mainType == "PLATFORM")
		return GetPlatformObject(str);
	else if(mainType == "WEAPON")
		return GetWeaponObject(str);
	else if(mainType == "AMMO")
		return GetAmmoObject(str);
	else if(mainType == "MONSTER")
		return GetMonsterObject(str);
	else if(mainType == "ENDLEVELBUTTON")
		return GetEndLevelButtonObject(str);	
	else if(mainType == "SPRITE")
		return GetSpriteObject(str);
	else if(mainType == "BACKGROUND")
	{
		GetBackgroundTexture(str);
		return nullptr;
	}
	else
	{
#ifdef _DEBUG
		printf("> ERROR! MapFileReader::ParseRecord - mainType: invalid value '%s'\n", mainType);
#endif
		return nullptr;
	};
}

MapFileReader::MapFileReader( 	DrawableComponentManager  *DCM, PhysicsComponentManager	*PCM, LogicComponentManager	*LCM) 
	:DCM(DCM),PCM(PCM),LCM(LCM), PlayerPhysicsComponent(nullptr)
{
}
