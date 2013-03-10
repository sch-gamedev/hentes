/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _SOUND_H_
#define _SOUND_H_

#include <string>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "resource.h"

class Sound : public Resource
{
	bool			m_bLoaded;

	sf::SoundBuffer	m_cSoundBuffer;
	sf::Sound		m_cSound;

public:

	Sound(std::string _id): m_bLoaded(false) { this->ID = _id; }

	void Create(const std::string _filename);

	virtual void Destroy();

	virtual bool Loaded() const;

	void SetVolume(int volume);

	void Play();
};

#endif // _SOUND_H_