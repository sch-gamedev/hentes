/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "audioconfigfilereader.h"

AudioConfigItem AudioConfigFileReader::ParseRecord(std::string str)
{
	size_t idx;

	AudioConfigItem result;

	if ((idx = str.find(' ')) != std::string::npos)
	{
		result.ID		= str.substr(0, idx);
		result.filename	= str.substr(idx + 1);
	}

	return result;
}