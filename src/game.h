/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class GameState;


/*****
A játék fő osztálya.
*****/
class Game
{
private :
	sf::RenderWindow Window;						// SFML ablak

	sf::Font GameFont;								// SFML font, ezt használjuk mindenhol

	enum STATE										// CurrentState lehetséges értékei
	{
		MENU_STATE = 0,
		IN_GAME_STATE,
		NUMBER_OF_STATES
	};
	GameState		 *States[NUMBER_OF_STATES];		// játékállapotok
	STATE			 CurrentState;					// aktuális játékállapot

	bool			running;


public :
	// konstruktor
	Game(unsigned int Width_in, unsigned int Height_in, const std::string &Title_in);

	// destruktor
	~Game();

	// inicializálás
	void Init();

	// vetítés beállítása (ablak létrehozásakor, átméretezésekor)
	void SetProjection(GLsizei Width_in, GLsizei Height_in);

	// a játék futtatása
	void Run();

	// a játék leállítása
	void ExitGame();

	// játékállapot váltása - irány a főmenü
	void GoToMenu();

	// játékállapot váltása - irány a játék; paraméter a betöltendő pálya neve (elérési útvonala)
	void GoToGame(const std::string &Path_in);

	// ablak referencia lekérése
	sf::RenderWindow* GetRenderWindow() { return &Window; };

	// font referencia lekérése
	const sf::Font& GetFont() { return GameFont; }
};


#endif
