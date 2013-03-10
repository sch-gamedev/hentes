/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _SOUNDSYSTEM_H_
#define _SOUNDSYSTEM_H_

#include <SFML/Audio.hpp>
#include <map>

// Forward declaration
class Sound;

class SoundSystem
{
	static SoundSystem*	s_instance;

	int		m_uSfxVolume;
	int		m_uMusicVolume;

	std::map<std::string, Sound*>	m_mSounds;

	sf::Music	m_cMusic;

	SoundSystem();
	SoundSystem(const SoundSystem&) { }
	SoundSystem& operator= (const SoundSystem&) { }
public:

	// Singleton p�ld�ny elk�r�se
	// FIGYELEM !!! Nem thread-safe !
	static SoundSystem* Instance();

	void Initialize();
	void Deinitialize();

	int GetSfxVolume()		{ return m_uSfxVolume; }
	int GetMusicVolume()	{ return m_uMusicVolume; }

	void SetSfxVolume(int volume);
	void SetMusicVolume(int volume);

	void FireSoundEvent(std::string sndEvtName);
};

#endif // _SOUNDSYSTEM_H_