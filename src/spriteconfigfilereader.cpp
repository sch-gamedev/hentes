/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "spriteconfigfilereader.h"
#include <assert.h>

SpriteConfig SpriteConfigFileReader::ParseRecord(std::string str)
{
	SpriteConfig result;

	char id[200];
	char texName[200];
	char action[200];

	if (sscanf(str.c_str(), "%s%s%u%u%f%s", id, texName, &result.rows, &result.columns, &result.duration, action) != 6)
	{
#ifdef _DEBUG
		printf("> ERROR! SpriteConfigFileReader::ParseRecord - parsing failed!\n");
#endif
	}

	result.ID = id;
	result.textureName = texName;
	
	if (strcmp(action, "REPEAT_SCENE") == 0)
	{
		result.action = Scene::REPEAT_SCENE;
	}
	else if (strcmp(action, "NEXT_SCENE") == 0)
	{
		result.action = Scene::NEXT_SCENE;
	}
	else if( strcmp(action, "STOP_PLAYING") == 0)
	{
		result.action = Scene::STOP_PLAYING;
	}
	else
	{
#ifdef _DEBUG
		printf("> ERROR! SpriteConfigFileReader::ParseRecord - action: invalid value (%s)\n", action);
#endif
		result.action = Scene::STOP_PLAYING;
	}

	return result;
}