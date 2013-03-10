/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _AUDIOCONFIGFILEREADER_H_
#define _AUDIOCONFIGFILEREADER_H_

#include "configfilereaderbase.hpp"

struct AudioConfigItem
{
	std::string ID;
	std::string filename;
};

class AudioConfigFileReader : public ConfigFileReaderBase<AudioConfigItem>
{
	AudioConfigFileReader(const AudioConfigFileReader&) { }
	AudioConfigFileReader& operator= (const AudioConfigFileReader&) { }
protected:
	virtual AudioConfigItem ParseRecord(std::string str);

public:
	AudioConfigFileReader() { }
};

#endif