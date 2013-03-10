/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "game.h"
#include "ingamestate.h"
#include "menustate.h"
#include "soundsystem.h"
#include "spriteconfigmanager.h"

/*****
konstruktor; ablak létrehozása
*****/
Game::Game(unsigned int Width_in, unsigned int Height_in, const std::string &Title_in):
	running(true)
{
	// ablak létrehozása
	Window.create(sf::VideoMode(Width_in, Height_in), Title_in
#if (defined _DEBUG)
        );
#else
        , sf::Style::Titlebar); // végső változatban ez lesz, fejlesztés idején még nem
#endif
}

/*****
destruktor; játékállapot objektumok felszabadítása
*****/
Game::~Game()
{
	for( int i = 0; i < NUMBER_OF_STATES; i++ )
	{
		delete States[i];
	}
}

/*****
Inicializálás; vetítés beállítása, erőforrások betöltése, stb.
*****/
void Game::Init()
{
	// V-sync bekapcsolása
	Window.setVerticalSyncEnabled(true);

	// randomizer
	srand((unsigned int)time(NULL));

	// lenyomva tartott billentyűk esetén se kapjunk folyamatosan KeyPressed üzeneteket
	Window.setKeyRepeatEnabled(false);

	// font betöltése
	GameFont.loadFromFile("Content/Fonts/youmurdererbb_reg.ttf");

	// vetítés beállítása
	SetProjection(Window.getSize().x, Window.getSize().y);

	// egyéb OpenGL beállítások
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.f, 1.f, 1.f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// játékállapot objektumok létrehozása
	States[MENU_STATE] = new MenuState(this);
	States[IN_GAME_STATE] = new InGameState(this);

	// hangrendszer inicializálsa
	SoundSystem::Instance()->Initialize();

	// sprite-ok inicializálása
	SpriteConfigManager::Instance()->Initialize();

	// menü állapotban induljon a játék
	GoToMenu();
}

/*****
A játék futtatása; main loop
*****/
void Game::Run()
{
	// main loop
	sf::Clock clock;
	sf::Int64 sum_time = 0;
    while( running )
    {
		// előző frame óta eltelt idő lekérdezése
		sum_time += clock.restart().asMicroseconds();

		// fix 50 Hz-cel fusson a program
		while( sum_time >= 20000 )
		{
			sum_time -= 20000;

			// események kezelése
			sf::Event event;
			while( Window.pollEvent(event) )
			{
				switch( event.type )
				{
					// ablak bezárása
					case sf::Event::Closed :
					{
						running = false;
						break;
					}

					// ablak átméreteződött
					case sf::Event::Resized :
					{
						SetProjection(event.size.width, event.size.height);
						break;
					}
				}
			}

			// az aktuális játékállapot léptetése
			States[CurrentState]->Update();
			// az aktuális játékállapot megjelenítése
			States[CurrentState]->Draw();
			Window.display();
		}
    }

	SoundSystem::Instance()->Deinitialize();
	SpriteConfigManager::Instance()->Deinitialize();
}

/*****
Kilépés a játékból
*****/
void Game::ExitGame()
{
	running = false;
}

/*****
Vetítés beállítása (ablak létrehozásakor, átméretezésekor)
*****/
void Game::SetProjection(GLsizei Width_in, GLsizei Height_in)
{
	// vetítés beállítása
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1024, 0, 768, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	
	// viewport beállítása a teljes ablakra
	glViewport(0, 0, Width_in, Height_in);
}

/*****
Játékállapot váltása - irány a főmenü
*****/
void Game::GoToMenu()
{
	CurrentState = MENU_STATE;
}

/*****
Játékállapot váltása - irány a játék
*****/
void Game::GoToGame(const std::string &Path_in)
{
	((InGameState*)States[IN_GAME_STATE])->LoadMap(Path_in);
	CurrentState = IN_GAME_STATE;
}
