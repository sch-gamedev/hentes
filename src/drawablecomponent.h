/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _DRAWABLECOMPONENT_H_
#define _DRAWABLECOMPONENT_H_

#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include "component.h"


/*****
Frame struktúra: egy sprite egy képkockájához tartozó textúrakoordinátákat tárolja
*****/
struct Frame
{
	float TCLowerLeft[2];														// bal alsó sarok textúrakoordinátái...
	float TCLowerRight[2];
	float TCUpperRight[2];
	float TCUpperLeft[2];

	// konstruktor
	Frame()
	{
		Clear();
	}

	// inicializálás
	void Clear()
	{
		// alapesetben a teljes textúrát használja, nem egy kis részét
		TCLowerLeft[0] = TCLowerLeft[1] = TCLowerRight[1] = TCUpperLeft[0] = 0;
		TCLowerRight[0] = TCUpperRight[0] = TCUpperRight[1] = TCUpperLeft[1] = 1;
	}

	// textúrakoordináták beállítása egyszerre, a bal alsó és a jobb felsõ sarok megadásával
	void SetTextureCoordinates(float LowerLeftX_in, float LowerLeftY_in, float UpperRightX_in, float UpperRightY_in)
	{
		TCLowerLeft[0]  = LowerLeftX_in;
		TCLowerLeft[1]  = LowerLeftY_in;
		TCUpperRight[0] = UpperRightX_in;
		TCUpperRight[1] = UpperRightY_in;
		TCLowerRight[0] = TCUpperRight[0];
		TCLowerRight[1] = TCLowerLeft[1];
		TCUpperLeft[0]  = TCLowerLeft[0];
		TCUpperLeft[1]  = TCUpperRight[1];
	}
};


/*****
Scene osztály: egy megjeleníthető komponens egy jelenete.
Minden Scene frame-ekbõl áll, és megszabható, hogy hány ezredmásodpercig tartson.
*****/
class Scene
{
public :
	// Bizonyos eseményekkor történõ akciók listája
	enum ACTION
	{
		REPEAT_SCENE,															// aktuális jelenet ismétlése
		NEXT_SCENE,																// ugrás a következõ jelenetre (az utolsóról a legelsõre)
		STOP_PLAYING															// animálás leállítása
	};


private :
	std::vector<Frame> Frames;													// a jelenet képkockái
	size_t				IndexOfCurrentFrame;									// a jelenet az ennyiedik képkockánál tart
	float				Duration;												// a jelenet hossza, ezredmásodpercben
	float				FrameTime;												// az egy frame-re jutó idõ, ezredmásodpercben (=Duration/Frames.size())
	float				ElapsedTime;											// az utolsó frame-lépés óta összesen eltelt idõ
	bool				Finished;												// a scene a végére ért
	ACTION				OnFinish;												// a jelenet végén történõ akció


public :
	// konstruktor
	Scene(void)
	{
		Clear();
	}

	// objektum inicializálása
	void Clear();

	// a scene frissítése = animáció
	void Update(float DeltaTime_in);

	// jelenet hosszának lekérdezése és beállítása
	float GetDuration() const
	{
		return Duration;
	}

	void SetDuration(float Duration_in)
	{
		Duration  = Duration_in;
		FrameTime = (Frames.size() > 0) ? (Duration / Frames.size()) : 0;
		Finished  = false;
	}

	// egy képkockára jutó idõtartam lekérdezése
	float GetFrameTime() const
	{
		return FrameTime;
	}

	// a jelenetben lévõ képkockák darabszámának lekérdezése
	size_t GetNumberOfFrames() const
	{
		return Frames.size();
	}

	// frame beszúrása a scene végére
	void AddFrame(const Frame &Frame_in)
	{
		Frames.push_back(Frame_in);
		FrameTime = Duration / Frames.size();
		Finished = false;
	}

	// pointer lekérése, amely az aktuális képkockára mutat
	Frame *GetCurrentFramePointer()
	{
		return (Frames.size() > 0) ? &Frames[IndexOfCurrentFrame] : NULL;
	}

	// megadott sorszámú frame-re mutató pointer lekérése
	Frame *AccesFrame(size_t Index_in);

	// aktuális frame indexének lekérdezése
	size_t GetIndexOfCurrentFrame() const
	{
		return IndexOfCurrentFrame;
	}

	// ugrás a paraméterül kapott sorszámú frame-re
	void JumpToFrame(size_t FrameNumber_in);

	// lekérdezés, hogy véget ért-e a scene
	bool GetFinished() const
	{
		return Finished;
	}

	// beállítás...
	void SetFinished(bool Finished_in)
	{
		Finished = Finished_in;
	}

	// jelenet végén történõ akció lekérdezése / beállítása
	ACTION GetOnFinish() const
	{
		return OnFinish;
	}

	void SetOnFinish(ACTION Action_in)
	{
		OnFinish = Action_in;
	}
};


/*****
Megjeleníthető komponensek osztálya
*****/
class DrawableComponent : public Component
{
public :
	// Koordináta-terek, amelyekben a koordináták megadhatók
	enum COORDINATE_SPACE
	{
		SCREEN_SPACE,															// világ koordinátatér (ideális pl pályaelemekhez, játékosokhoz)
		WORLD_SPACE																// képernyő koordinátatér (ideális pl HUD-hoz)
	};

	float			    Width;													// a sprite szélessége
	float			    Height;													// a sprite magassága
	sf::Vector2f	    Position;												// a komponens bal alsó sarkának koordinátái CoordinateSpace térben

private :
	COORDINATE_SPACE    CoordinateSpace;										// koordináta-tér
	size_t			    TextureID;												// a sprite által használt textúra azonosítója
	bool			    FlippedHorizontally;									// vízszintesen tükrözve van-e
	bool			    FlippedVertically;										// függõlegesen tükrözve van-e
	Frame			    *CurrentFrame;											// pointer az aktuális képkockára, ez renderelõdik mindig
	size_t  		    IndexOfCurrentScene;									// aktuális scene indexe a Scenes vektorban
	std::vector<Scene> Scenes;													// jeleneteket tartalmazó vektor
	bool				Stopped;	
	sf::Vector2f		RelativePositionFromHitbox;								// Amikor megkapjuk az üzenetet, hogy hova került a Physical component, akkor ennyivel kell eltolni a megjelenítést ahoz képest
	// az animálás le van-e állítva


public :
	// konstruktor
	DrawableComponent(GameObject *OwnerGameObject_in);

	// inicializálás
	void Clear();

	// a legfontosabb értékek beállítása egyetlen függvény segítségével
	void Set(float Width_in, float Height_in, sf::Vector2f Position_in, size_t TextureID_in, COORDINATE_SPACE CoordinateSpace_in = WORLD_SPACE, bool FlippedHorizontally_in = false, bool FlippedVertically_in = false, bool Stopped_in = false);

	// animált sprite létrehozása egy lépésben
	void CreateAnimatedSprite(unsigned NumberOfRows_in, unsigned NumberOfColumns_in, float Duration_in, Scene::ACTION OnLastSceneFinished_in);

	// üzenet fogadása
	virtual void ReciveMessage(const Message &Message_in);
	
	// komponens frissítése
	virtual void Update();

	// komponens megjelenítése
	void Draw();

	// textúra azonosító lekérdezése/beállítása
	size_t GetTextureID(void) const
	{
		return TextureID;
	}
	
	void SetTextureID(size_t ID_in)
	{
		TextureID = ID_in;
	}

	// koordináta-tér lekérdezése/beállítása
	COORDINATE_SPACE GetCoordinateSpace(void) const
	{
		return CoordinateSpace;
	}

	void SetCoordinateSpace(COORDINATE_SPACE CoordinateSpace_in)
	{
		CoordinateSpace = CoordinateSpace_in;
	}

	// tükrözés lekérdezése / beállítása
	bool GetFlippedHorizontally(void) const
	{
		return FlippedHorizontally;
	}

	bool GetFlippedVertically(void) const
	{
		return FlippedVertically;
	}

	void SetFlippedHorizontally(bool FlippedHorizontally_in)
	{
		FlippedHorizontally = FlippedHorizontally_in;
	}

	void SetFlippedVertically(bool FlippedVertically_in)
	{
		FlippedVertically = FlippedVertically_in;
	}

	void SetFlipped(bool FlippedHorizontally_in, bool FlippedVertically_in)
	{
		FlippedHorizontally = FlippedHorizontally_in;
		FlippedVertically = FlippedVertically_in;
	}

	// scene elérése: pointert ad vissza a paraméterül kapott indexû scene-re
	Scene *AccessScene(size_t Index_in);

	// aktuális scene elérése
	Scene *AccessCurrentScene(void)
	{
		return (Scenes.size() > 0) ? &Scenes[IndexOfCurrentScene] : NULL;
	}

	// jelenetek számának lekérdezése
	size_t GetNumberOfScenes(void) const
	{
		return Scenes.size();
	}

	// jelenet beszúrása
	void AddScene(Scene &NewScene_in)
	{
		Scenes.push_back(NewScene_in);
	}

	// ugrás a megadott scene megadott frame-ére
	void JumpToScene(size_t SceneNumber_in, size_t FrameNumber_in = 0);

	// aktuális scene sorszámának lekérdezése
	size_t GetIndexOfCurrentScene() const
	{
		return IndexOfCurrentScene;
	}

	// animáció indítása/leállítása, érték lekérdezése
	bool IsPlaying() const
	{
		return !Stopped;
	}

	void StopAnimation()
	{
		Stopped = true;
	}

	void StartPlaying()
	{
		Stopped = false;
	}

	void SetRelativePositionFromHitbox(sf::Vector2f rPos) 
	{
		RelativePositionFromHitbox = rPos;
	}
};

#endif
