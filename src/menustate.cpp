/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "menustate.h"
#include "soundsystem.h"
#include "soundeventtypes.h"
#include "game.h"

MenuState::MenuState(Game *GamePointer_in) :
	GameState(GamePointer_in),
	m_uCurrentMenuItem(0),
	m_uCurrentSelectedLevel(0),
	m_bInOptionsMenu(false),
	m_uCurrentMapIndex(0)
{
	const sf::Font& font = GamePointer->GetFont();

	m_bWasButtonPressed[0] = false;
	m_bWasButtonPressed[1] = false;
	m_bWasButtonPressed[2] = false;
	m_bWasButtonPressed[3] = false;
	m_bWasButtonPressed[4] = false;

	m_cHeaderText.setString("HENTES");
	m_cHeaderText.setCharacterSize(200);
	m_cHeaderText.setPosition(350, 50);
	m_cHeaderText.setColor(sf::Color::Red);
	m_cHeaderText.setFont(font);

	m_aMenuItems[0].setString("Start Game");
	m_aMenuItems[0].setCharacterSize(40);
	m_aMenuItems[0].setPosition(300, 330);
	m_aMenuItems[0].setColor(sf::Color::Red);
	m_aMenuItems[0].setFont(font);

	m_aMenuItems[1].setString("Options");
	m_aMenuItems[1].setCharacterSize(40);
	m_aMenuItems[1].setPosition(300, 430);
	m_aMenuItems[1].setColor(sf::Color::Red);
	m_aMenuItems[1].setFont(font);

	m_aMenuItems[2].setString("Exit Game");
	m_aMenuItems[2].setCharacterSize(40);
	m_aMenuItems[2].setPosition(300, 530);
	m_aMenuItems[2].setColor(sf::Color::Red);
	m_aMenuItems[2].setFont(font);

	m_aOptionsMenuItems[0].setString("SFX Volume");
	m_aOptionsMenuItems[0].setCharacterSize(40);
	m_aOptionsMenuItems[0].setPosition(300, 330);
	m_aOptionsMenuItems[0].setColor(sf::Color::Red);
	m_aOptionsMenuItems[0].setFont(font);

	m_aOptionsMenuItems[1].setString("Music Volume");
	m_aOptionsMenuItems[1].setCharacterSize(40);
	m_aOptionsMenuItems[1].setPosition(300, 430);
	m_aOptionsMenuItems[1].setColor(sf::Color::Red);
	m_aOptionsMenuItems[1].setFont(font);

	m_aOptionsMenuItems[2].setString("Back");
	m_aOptionsMenuItems[2].setCharacterSize(40);
	m_aOptionsMenuItems[2].setPosition(300, 530);
	m_aOptionsMenuItems[2].setColor(sf::Color::Red);
	m_aOptionsMenuItems[2].setFont(font);

	m_cSfxVolumeText.setString("10");
	m_cSfxVolumeText.setCharacterSize(60);
	m_cSfxVolumeText.setPosition(800, 330);
	m_cSfxVolumeText.setColor(sf::Color::Red);
	m_cSfxVolumeText.setFont(font);

	m_cMusicVolumeText.setString("10");
	m_cMusicVolumeText.setCharacterSize(60);
	m_cMusicVolumeText.setPosition(800, 430);
	m_cMusicVolumeText.setColor(sf::Color::Red);
	m_cMusicVolumeText.setFont(font);

	m_cMaps.Initialize();

	m_cCurrentMapText.setCharacterSize(40);
	m_cCurrentMapText.setPosition(680, 350);
	m_cCurrentMapText.setColor(sf::Color::Red);
	m_cCurrentMapText.setFont(font);

	UpdateCurrentMapText();

	m_sLogoState.size		= 200;
	m_sLogoState.positionX	= 350;
	m_sLogoState.positionY	= 50;
	m_sLogoState.rotation	= 0;
	m_sLogoState.step		= 100;

}

/*****
friss�t�s; inputkezel�s
*****/
void MenuState::Update()
{
	// Lefel� kurozrny�l kezel�se
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_bWasButtonPressed[DOWN_BUTTON] == false)
	{
		m_bWasButtonPressed[DOWN_BUTTON] = true;
		SoundSystem::Instance()->FireSoundEvent("MENU_SELECT");

		if (m_bInOptionsMenu)
		{
			m_uCurrentOptionsMenuItem = ++m_uCurrentOptionsMenuItem % NUM_OPTIONSMENUITEMS;
		}
		else
		{
			m_uCurrentMenuItem = ++m_uCurrentMenuItem % NUM_MENUITEMS;
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_bWasButtonPressed[DOWN_BUTTON] = false;
	}

	// Felfel� kurzorny�l kezel�se
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_bWasButtonPressed[UP_BUTTON] == false)
	{
		m_bWasButtonPressed[UP_BUTTON] = true;
		SoundSystem::Instance()->FireSoundEvent("MENU_SELECT");

		if (m_bInOptionsMenu)
		{
			m_uCurrentOptionsMenuItem = (--m_uCurrentOptionsMenuItem + NUM_OPTIONSMENUITEMS) % NUM_OPTIONSMENUITEMS;
		}
		else
		{
			m_uCurrentMenuItem = (--m_uCurrentMenuItem + NUM_MENUITEMS) % NUM_MENUITEMS;
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_bWasButtonPressed[UP_BUTTON] = false;
	}

	// Balra kurzorny�l kezel�se
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_bWasButtonPressed[LEFT_BUTTON] == false)
	{
		m_bWasButtonPressed[LEFT_BUTTON] = true;

		if (m_bInOptionsMenu)
		{
			if (m_uCurrentOptionsMenuItem == SFX_VOLUME)
			{
				int newVolume = SoundSystem::Instance()->GetSfxVolume() - 1;
				SoundSystem::Instance()->SetSfxVolume(newVolume);

				char strVolume[3];
				newVolume = SoundSystem::Instance()->GetSfxVolume();
				sprintf_s(strVolume, "%u", newVolume);

				m_cSfxVolumeText.setString(strVolume);
				SoundSystem::Instance()->FireSoundEvent("MENU_SELECT");
			}
			else if (m_uCurrentOptionsMenuItem == MUSIC_VOLUME)
			{
				int newVolume = SoundSystem::Instance()->GetMusicVolume() - 1;
				SoundSystem::Instance()->SetMusicVolume(newVolume);

				char strVolume[3];
				newVolume = SoundSystem::Instance()->GetMusicVolume();
				sprintf_s(strVolume, "%u", newVolume);
				// TODO REMOVE sprintf_s and replace with ANSI-compliant stuff
				m_cMusicVolumeText.setString(strVolume);
				SoundSystem::Instance()->FireSoundEvent("MENU_SELECT");
			}
		}
		else
		{
			if (m_uCurrentMenuItem == START_GAME)
			{
				// MAP selection
				m_uCurrentMapIndex = (--m_uCurrentMapIndex + m_cMaps.GetNumMaps()) % m_cMaps.GetNumMaps();
				UpdateCurrentMapText();
				SoundSystem::Instance()->FireSoundEvent("MENU_SELECT");
			}
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_bWasButtonPressed[LEFT_BUTTON] = false;
	}

	// Jobbra kurzorny�l kezel�se
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_bWasButtonPressed[RIGHT_BUTTON] == false)
	{
		m_bWasButtonPressed[RIGHT_BUTTON] = true;

		if (m_bInOptionsMenu)
		{
			if (m_uCurrentOptionsMenuItem == SFX_VOLUME)
			{
				int newVolume = SoundSystem::Instance()->GetSfxVolume() + 1;
				SoundSystem::Instance()->SetSfxVolume(newVolume);

				char strVolume[3];
				newVolume = SoundSystem::Instance()->GetSfxVolume();
				sprintf_s(strVolume, "%u", newVolume);

				m_cSfxVolumeText.setString(strVolume);
				SoundSystem::Instance()->FireSoundEvent("MENU_SELECT");
			}
			else if (m_uCurrentOptionsMenuItem == MUSIC_VOLUME)
			{
				int newVolume = SoundSystem::Instance()->GetMusicVolume() + 1;
				SoundSystem::Instance()->SetMusicVolume(newVolume);

				char strVolume[3];
				newVolume = SoundSystem::Instance()->GetMusicVolume();
				sprintf_s(strVolume, "%u", newVolume);

				m_cMusicVolumeText.setString(strVolume);
				SoundSystem::Instance()->FireSoundEvent("MENU_SELECT");
			}
		}
		else
		{
			if (m_uCurrentMenuItem == START_GAME)
			{
				// MAP selection
				m_uCurrentMapIndex = (++m_uCurrentMapIndex + m_cMaps.GetNumMaps()) % m_cMaps.GetNumMaps();
				UpdateCurrentMapText();
				SoundSystem::Instance()->FireSoundEvent("MENU_SELECT");
			}
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_bWasButtonPressed[RIGHT_BUTTON] = false;
	}

	// Enter kezel�se
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && m_bWasButtonPressed[ENTER_BUTTON] == false)
	{
		m_bWasButtonPressed[ENTER_BUTTON] = true;
		
		std::string mapString;

		if (!m_bInOptionsMenu)
		{
			switch (m_uCurrentMenuItem)
			{
				case START_GAME:
					// mapek beolvas�sa �s v�laszt�s k�z�tt�k
					mapString = m_cMaps.GetMap(m_uCurrentMapIndex);
					mapString.insert(0, MapsBrowser::MapsDirectory);
					GamePointer->GoToGame(mapString);
					break;

				case OPTIONS:
					m_bInOptionsMenu = true;
					m_uCurrentOptionsMenuItem = 0;
					break;

				case EXIT_GAME:
					GamePointer->ExitGame();
					break;
			}
		}
		else
		{
			switch (m_uCurrentOptionsMenuItem)
			{
				case SFX_VOLUME:
					break;

				case MUSIC_VOLUME:
					break;

				case BACK:
					m_bInOptionsMenu = false;
					m_uCurrentMenuItem = 0;
					break;
			}
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		m_bWasButtonPressed[ENTER_BUTTON] = false;
	}

	// Log� (HENTES felirat) juice (mozg�s)
	UpdateLogoJuice();
}

/*****
renderel�s
*****/
void MenuState::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sf::RenderWindow* window = GamePointer->GetRenderWindow();

	// OpenGL �llapotok elment�se
	window->pushGLStates();


	window->draw(m_cHeaderText);

	if (!m_bInOptionsMenu)
	{
		for (unsigned int i = 0; i < NUM_MENUITEMS; i++)
		{
			if (i == m_uCurrentMenuItem)
			{
				m_aMenuItems[i].setCharacterSize(90);
				m_aMenuItems[i].setPosition(270.0f, 315.0f + i * 100);
			}
			else
			{
				m_aMenuItems[i].setCharacterSize(60);
				m_aMenuItems[i].setPosition(300.0f, 330.0f + i * 100);
			}

			window->draw(m_aMenuItems[i]);
		}

		window->draw(m_cCurrentMapText);
	}
	else
	{
		for (unsigned int i = 0; i < NUM_OPTIONSMENUITEMS; i++)
		{
			if (i == m_uCurrentOptionsMenuItem)
			{
				m_aOptionsMenuItems[i].setCharacterSize(90);
				m_aOptionsMenuItems[i].setPosition(270.0f, 315.0f + i * 100);
			}
			else
			{
				m_aOptionsMenuItems[i].setCharacterSize(60);
				m_aOptionsMenuItems[i].setPosition(300.0f, 330.0f + i * 100);
			}

			window->draw(m_aOptionsMenuItems[i]);
		}

		window->draw(m_cSfxVolumeText);
		window->draw(m_cMusicVolumeText);
	}

	// OpenGL �llapotok vissza�ll�t�sa
	window->popGLStates();
}

void MenuState::UpdateLogoJuice()
{

	if (++m_sLogoState.step > 7)
	{
		m_sLogoState.size = (180 + rand() % 40);
		m_sLogoState.positionX = (300 + rand() % 50);
		m_sLogoState.positionY = ( 25 + rand() % 50);
		m_sLogoState.step = 0;
	}

	m_cHeaderText.setCharacterSize(m_sLogoState.size);
	m_cHeaderText.setPosition(m_sLogoState.positionX, m_sLogoState.positionY);

}

void MenuState::UpdateCurrentMapText()
{
	std::string mapName = m_cMaps.GetMap(m_uCurrentMapIndex);
	mapName.insert(0, "<  ");
	mapName.insert(mapName.size(), "  >");
	m_cCurrentMapText.setString(mapName);
}

