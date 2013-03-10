/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _MENUSTATE_H_
#define _MENUSTATE_H_

#include "gamestate.h"
#include "mapsbrowser.h"

class Game;

/*****
Men� j�t�k�llapot oszt�lya.
*****/
class MenuState : public GameState
{
	enum MenuButtons		{ UP_BUTTON = 0, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON, ENTER_BUTTON, NUM_USEDBUTTONS };
	enum MenuItems			{ START_GAME = 0, OPTIONS, EXIT_GAME, NUM_MENUITEMS };
	enum OptionsMenuItems	{ SFX_VOLUME = 0, MUSIC_VOLUME, BACK, NUM_OPTIONSMENUITEMS };

	unsigned int	m_uCurrentMenuItem;
	unsigned int	m_uCurrentSelectedLevel;
	unsigned int	m_uCurrentOptionsMenuItem;
	
	sf::Text		m_cHeaderText;
	sf::Text		m_aMenuItems[NUM_MENUITEMS];
	sf::Text		m_aOptionsMenuItems[NUM_OPTIONSMENUITEMS];
	sf::Text		m_cSfxVolumeText;
	sf::Text		m_cMusicVolumeText;

	bool			m_bWasButtonPressed[NUM_USEDBUTTONS];

	bool			m_bInOptionsMenu;

	MapsBrowser		m_cMaps;
	sf::Text		m_cCurrentMapText;
	unsigned int	m_uCurrentMapIndex;

	struct
	{
		unsigned short	size;
		unsigned short	positionX;
		unsigned short	positionY;
		unsigned short	rotation;
		unsigned short	step;
	} m_sLogoState;

	void UpdateLogoJuice();

	void UpdateCurrentMapText();

public :
	// konstruktor
	MenuState(Game *GamePointer_in);

	// friss�t�s; inputkezel�s
	virtual void Update();

	// renderel�s
	virtual void Draw();
};

#endif
