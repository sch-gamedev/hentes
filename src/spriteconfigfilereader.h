/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _SPRITECONFIGFILEREADER_H_
#define _SPRITECONFIGFILEREADER_H_

#include "configfilereaderbase.hpp"
#include "drawablecomponent.h"

struct SpriteConfig
{
	std::string		ID;
	std::string		textureName;
	size_t			textureId;
	unsigned int	rows;
	unsigned int	columns;
	float			duration;
	Scene::ACTION	action;
};

class SpriteConfigFileReader : public ConfigFileReaderBase<SpriteConfig>
{
	SpriteConfigFileReader(const SpriteConfigFileReader&) { }
	SpriteConfigFileReader& operator= (const SpriteConfigFileReader&) { }

protected:
	virtual SpriteConfig ParseRecord(std::string str);

public:
	SpriteConfigFileReader() {}
};

#endif