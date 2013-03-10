/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "soundsystem.h"
#include "sound.h"
#include "audioconfigfilereader.h"

SoundSystem::SoundSystem():
	m_uSfxVolume(10),
	m_uMusicVolume(10)
{
}

void SoundSystem::Initialize()
{
	AudioConfigFileReader reader;

	if (!reader.OpenFile("Content/Audio/audioconfig.txt"))
	{
		// ERROR
		exit(1);
	}

	while (reader.HasNextRecord())
	{
		AudioConfigItem item = reader.GetNextRecord();

		Sound* snd = new Sound(item.ID);

		snd->Create(item.filename.insert(0, "Content/Audio/"));
		snd->SetVolume(m_uSfxVolume);

		m_mSounds[item.ID] = snd;
	}

	m_cMusic.openFromFile("Content/Audio/music.ogg");
	m_cMusic.setLoop(true);
	m_cMusic.play();
}

void SoundSystem::Deinitialize()
{
	for (std::map<std::string, Sound*>::iterator it = m_mSounds.begin(); it != m_mSounds.end(); it++)
	{
		delete it->second;
	}

	delete s_instance;
}

void SoundSystem::SetSfxVolume(int volume)
{
	m_uSfxVolume = (volume + 11) % 11;

	for (std::map<std::string, Sound*>::iterator it = m_mSounds.begin(); it != m_mSounds.end(); it++)
	{
		it->second->SetVolume(m_uSfxVolume);
	}
}

void SoundSystem::SetMusicVolume(int volume)
{
	m_uMusicVolume = (volume + 11) % 11;

    m_cMusic.setVolume(m_uMusicVolume * 10.0f);
}

SoundSystem* SoundSystem::Instance()
{
	if (s_instance == NULL)
	{
		s_instance = new SoundSystem();
	}

	return s_instance;
}

void SoundSystem::FireSoundEvent(std::string sndEvtName)
{
	std::map<std::string, Sound*>::iterator sndIt = m_mSounds.find(sndEvtName);

	if (sndIt != m_mSounds.end())
	{
		sndIt->second->Play();
	}
}

SoundSystem* SoundSystem::s_instance = NULL;