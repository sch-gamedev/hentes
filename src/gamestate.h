/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

// elődeklarációk
class Game;

/*****
Játékállapotok (menu, ingame) absztrakt ősosztálya.
*****/
class GameState
{
protected :
    // a fő játékosztályra mutató pointer
	Game *GamePointer;


public :
	// konstruktor
	GameState(Game *GamePointer_in) : GamePointer(GamePointer_in)
	{
	}

	// frissítés - léptetés minden timestep-ben
	virtual void Update() = 0;

	// renderelés - a szükséges dolgok megjelenítése
	virtual void Draw() = 0;
};


#endif
