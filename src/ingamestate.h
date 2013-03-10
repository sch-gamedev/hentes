/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _INGAMESTATE_H_
#define _INGAMESTATE_H_

// elődeklarációk
class Game;

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include "gamestate.h"
#include "gameobject.h"
#include "drawablecomponent.h"
#include "drawablecomponentmanager.h"
#include "physicscomponent.h"
#include "physicscomponentmanager.h"
#include "logiccomponent.h"
#include "logiccomponentmanager.h"
#include "camera.h"
#include "bloodmanager.h"

/*****
Játék játékállapot osztálya.
*****/
class InGameState : public GameState
{
private :
	bool					  Paused;											// szüneteltetve van-e a játék (esc-et nyomott-e a játékos)
	std::list<GameObject *>	  GameObjects;										// a játékban szereplő objektumok listája (karakterek, pályaelemek, stb.)
	DrawableComponentManager  *DCM;												// megjeleníthető komponensek menedzsere
	PhysicsComponentManager	  *PCM;												// fizikai komponensek menedzsere
	LogicComponentManager	  *LCM;												// logika komponensek menedzsere

	PhysicsComponent		  *PlayerPhysicsComponent;							// a játékos fizikai komponense
	Camera					  Camera2D;											// a kameraojjektum, ami követi a játékost
	size_t					  BackgroundTextureIndex;							// háttérként felhasznált textúra indexe

	bool won;
	bool dead;

	sf::Text	pauseText;
	sf::Text	winText;
	sf::Text	deadText;

	sf::Text	instructionTextContinue;
	sf::Text	instructionTextExit;

	// összes játékobjektum törlése
	void DeleteAllGameObjects();
	std::vector<GameObject*> DeletedComponents;

public :
	// konstruktor
	InGameState(Game *GamePointer_in);

	// destruktor
	~InGameState();

	// pálya betöltése fájlból
	void LoadMap(const std::string &Path_in);

	// frissítés; inputkezelés
	virtual void Update();

	// renderelés
	virtual void Draw();

	// a pályát megnyerte
	void LevelWon();

	// meghalt a játékos
	void PlayerDead();
};

#endif
