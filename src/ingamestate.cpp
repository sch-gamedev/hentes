/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include <SFML/OpenGL.hpp>
#include "ingamestate.h"
#include "texturemanager.h"
#include "playerlogiccomponent.h"
#include "mapfilereader.h"
#include "bulletmanager.h"
#include "game.h"


/*****
Konstruktor
Component managerek létrehozása
*****/
InGameState::InGameState(Game *GamePointer_in) : GameState(GamePointer_in), Paused(false), won(false), dead(false)
{
	DCM = new DrawableComponentManager();
	PCM = new PhysicsComponentManager();
	LCM = new LogicComponentManager();

	const sf::Font& font = GamePointer->GetFont();

	pauseText.setString("Paused");
	pauseText.setCharacterSize(200);
	pauseText.setColor(sf::Color::Red);
	pauseText.setPosition(300, 50);
	pauseText.setFont(font);

	winText.setString("Level complete!");
	winText.setCharacterSize(200);
	winText.setColor(sf::Color::Red);
	winText.setPosition(25, 50);
	winText.setFont(font);

	deadText.setString("You are dead");
	deadText.setCharacterSize(200);
	deadText.setColor(sf::Color::Red);
	deadText.setPosition(150, 50);
	deadText.setFont(font);

	instructionTextContinue.setString("Left shift: continue");
	instructionTextContinue.setCharacterSize(60);
	instructionTextContinue.setColor(sf::Color::Red);
	instructionTextContinue.setPosition(200, 450);
	instructionTextContinue.setFont(font);

	instructionTextExit.setString("C: exit to menu");
	instructionTextExit.setCharacterSize(60);
	instructionTextExit.setColor(sf::Color::Red);
	instructionTextExit.setPosition(200, 550);
	instructionTextExit.setFont(font);
}

/*****
Destruktor
Component managerek felszabadítása
*****/
InGameState::~InGameState()
{
	delete DCM;
	delete PCM;
	delete LCM;
}

/*****
összes játékobjektum törlése
*****/
void InGameState::DeleteAllGameObjects()
{
	// a betöltött játékobjektumok törlése, felszabadítása, kiregisztrálása...
	DCM->UnRegisterAllComponents();
	PCM->UnRegisterAllComponents();
	LCM->UnRegisterAllComponents();
	//BulletManager::getInstance().removeAllBullets();
	for( std::list<GameObject *>::iterator i = GameObjects.begin(); i != GameObjects.end(); i++ )
	{
		delete (*i);
	}
	GameObjects.clear();
}

/*****
pálya betöltése fájlból
*****/
void InGameState::LoadMap(const std::string &Path_in)
{
	BulletManager::getInstance().setManagers(LCM,PCM,DCM);
	// összes eddig betöltött objektumtól (előzőleg betöltött pálya pl.) megszabadulunk
	DeleteAllGameObjects();

	// korábban lerakott vér emitterek törlése
	BloodManager::Instance().ResetAllEmitters();

	// ki kell törölni a bulleteket
	BulletManager::getInstance().removeAllBullets();

	// Nincs megállítva a játék
	Paused = false;
	dead = false;
	won = false;
		
	// ezt vissza kell állítani, mert valahol, valaki elcseszi (sfml)
	glMatrixMode(GL_MODELVIEW);

	MapFileReader reader(DCM,PCM,LCM);
	reader.OpenFile(Path_in);
	while( reader.HasNextRecord()) {
		GameObject* tmp = reader.GetNextRecord();
		if (tmp!=0) {
			tmp->setOwner(this);
			GameObjects.push_back(tmp);
		}
	}
	
	BackgroundTextureIndex = reader.GetBackgroundTextureIndex();
	PlayerPhysicsComponent = reader.GetPlayerPhysicsComponent();
}


/*****
frissítés; inputkezelés
*****/
void InGameState::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !Paused && !dead && !won)
	{
		Paused = true;
	}

	if (Paused || dead || won)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			GamePointer->GoToMenu();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !won && !dead)
		{
			Paused = false;
		}

		return;
	}

	DeletedComponents.clear();
	for( std::list<GameObject*>::iterator it =  GameObjects.begin(); it != GameObjects.end(); ++it) { 
		if ((*it)->IsMarkedAsDeleted())
		{
			DeletedComponents.push_back(*it);	
		}
	}
	this->GameObjects.remove_if(Utility::MarkedAsDeletedPred<GameObject>());
	for ( std::vector<GameObject*>::iterator it = DeletedComponents.begin(); it != DeletedComponents.end(); ++it) 
	{
		delete *it;
	}
	// komponensek frissítése
	DCM->Update();
	PCM->Update();
	LCM->Update();

	// részecskerendszerek frissítése
	BloodManager::Instance().UpdateEmitters(20);
}

/*****
renderelés
*****/
void InGameState::Draw()
{
	// képernyő törlése
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// kamera elhelyezése
	sf::Vector2u window_size = GamePointer->GetRenderWindow()->getSize();
	Camera2D.position = PlayerPhysicsComponent->GetCenterPosition() - sf::Vector2f(window_size.x / 2.f, window_size.y / 2.f);
	Camera2D.Look();

	// IHOL KÖVETKEZÉK A BARTOSISTA HÁTTÉRKÉPKIHELYEZŐ RUTIN
	float tex_coord_s = 1024.f / TextureManager::Instance().GetTexturePointer(BackgroundTextureIndex)->GetWidth();
	float tex_coord_t = 768.f  / TextureManager::Instance().GetTexturePointer(BackgroundTextureIndex)->GetHeight();
	//static float t = 0.f;
	//t += 1.5f;
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();
	//float zoom = (sin(t* 3.1415f / 180.f)) + 1.2f;
	//glScalef(zoom, zoom, 1.f);
	//glRotatef((cos(t* 3.1415f / 180.f)) * 100, 0, 0, 1.f);
	glTranslatef(PlayerPhysicsComponent->GetCenterPosition().x / TextureManager::Instance().GetTexturePointer(BackgroundTextureIndex)->GetWidth(), PlayerPhysicsComponent->GetCenterPosition().y / TextureManager::Instance().GetTexturePointer(BackgroundTextureIndex)->GetHeight(), 0);
	TextureManager::Instance().BindTexture(BackgroundTextureIndex);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2i(0, 0);
		glTexCoord2f(tex_coord_s, 0);
		glVertex2i(1024, 0);
		glTexCoord2f(tex_coord_s, tex_coord_t);
		glVertex2i(1024, 768);
		glTexCoord2f(0, tex_coord_t);
		glVertex2i(0, 768);
	glEnd();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// összes megjeleníthető komponens kirajzoltatása
	DCM->Draw();
	
	// részecskerendszerek
	BloodManager::Instance().Render();
	glColor3f(1.f, 1.f, 1.f);

	sf::RenderWindow* window = GamePointer->GetRenderWindow();
	window->pushGLStates();

	if (Paused)
	{
		window->draw(pauseText);
		window->draw(instructionTextContinue);
	}

	if (won)
	{
		window->draw(winText);
	}

	if (dead)
	{
		window->draw(deadText);
	}

	if (Paused || won || dead)
	{
		window->draw(instructionTextExit);
	}

	window->popGLStates();
}

void InGameState::LevelWon()
{
	won = true;
}

void InGameState::PlayerDead()
{
	dead = true;
}

