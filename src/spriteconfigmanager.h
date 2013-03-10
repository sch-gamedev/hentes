/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _SPRITECONFIGMANAGER_H_
#define _SPRITECONFIGMANAGER_H_

#include <map>
#include "spriteconfigfilereader.h"

class SpriteConfigManager
{
	static SpriteConfigManager*	s_instance;

	std::map<std::string, SpriteConfig>	m_mSpriteConfigs;

	SpriteConfigManager();
	SpriteConfigManager(const SpriteConfigManager&) { }
	SpriteConfigManager& operator= (const SpriteConfigManager&) { }

public:

	static SpriteConfigManager* Instance();

	void Initialize();
	void Deinitialize();

	SpriteConfig LookupSpriteConfig(std::string ID);
};

#endif