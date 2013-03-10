/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "spriteconfigmanager.h"
#include "texturemanager.h"

SpriteConfigManager::SpriteConfigManager()
{
}

void SpriteConfigManager::Initialize()
{
	SpriteConfigFileReader reader;

	if (!reader.OpenFile("Content/Sprites/spriteconfig.txt"))
	{
		// ERROR
		exit(1);
	}

	while (reader.HasNextRecord())
	{
		SpriteConfig item = reader.GetNextRecord();

		TextureManager::Instance().LoadTexture(item.textureName.insert(0, "Content/Sprites/"), item.textureId);

		m_mSpriteConfigs[item.ID] = item;
	}
}

void SpriteConfigManager::Deinitialize()
{
	delete this;
	s_instance = nullptr;
}

SpriteConfig SpriteConfigManager::LookupSpriteConfig(std::string ID)
{
	auto it = m_mSpriteConfigs.find(ID);

	if (it != m_mSpriteConfigs.end())
	{
		return it->second;
	}
	else
	{
#ifdef _DEBUG
		printf("> ERROR! SpriteConfigManager::LookupSpriteConfig - cannot find config with ID '%s'\n", ID.c_str());
#endif
		return m_mSpriteConfigs.begin()->second;
	}
}

SpriteConfigManager* SpriteConfigManager::Instance()
{
	if (s_instance == NULL)
	{
		s_instance = new SpriteConfigManager();
	}

	return s_instance;
}

SpriteConfigManager* SpriteConfigManager::s_instance = NULL;