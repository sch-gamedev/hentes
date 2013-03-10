/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "sound.h"
#include <assert.h>

void Sound::Create(const std::string _filename)
{
	if (!m_cSoundBuffer.loadFromFile(_filename))
	{
		return;
	}

	m_cSound.setBuffer(m_cSoundBuffer);
	m_cSound.setLoop(false);
	m_cSound.setVolume(100);
	m_bLoaded = true;
}

void Sound::Destroy()
{
}

bool Sound::Loaded() const
{
	return m_bLoaded;
}

void Sound::SetVolume(int volume)
{
	assert(volume >= 0 && volume <= 10);
	m_cSound.setVolume(volume * 10.0f);
}

void Sound::Play()
{
	m_cSound.play();
}