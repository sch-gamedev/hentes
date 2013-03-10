/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include <sstream>
#include <cassert>
#include "texturemanager.h"
#include "drawablecomponent.h"


/*****
objektum inicializálása
alapesetben a scene üres, tehát a használathoz mindenképp hozzá kell adni manuálisan legalább egy darab frame-et
(AddFrame metódus)
*****/
void Scene::Clear()
{
	Frames.clear();
	Duration = FrameTime = ElapsedTime = 0.f;
	IndexOfCurrentFrame = 0;			// fontos, hogy valójában kezdetben üres a Frames vektor!
	Finished = true;
	OnFinish = NEXT_SCENE;
}

/*****
jelenet frissítése
*****/
void Scene::Update(float DeltaTime_in)
{
	// ha még nem ért a scene a végére
	if( !Finished )
	{
		// eltelt idõk összegzése
		ElapsedTime += DeltaTime_in;

		// ha elég idõ telt el, ugrás a következõ frame-re
		if( ElapsedTime >= FrameTime )
		{
			// ha az utolsó frame-en áll, vége az animációnak, egyébként ugrás a következõre
			if( IndexOfCurrentFrame >= Frames.size() - 1 )
			{
				Finished = true;
			}
			else
			{
				IndexOfCurrentFrame++;
			}

			// eltelt idõ nullázása
			ElapsedTime = 0;
		}
	}
}

/*****
Megadott sorszámú frame-re mutató pointer lekérése.
Érvénytelen argumentum esetén nullpointert ad vissza.
*****/
Frame *Scene::AccesFrame(size_t Index_in)
{
	if( Index_in < Frames.size() )
	{
		return &Frames[Index_in];
	}
	else
	{
		return NULL;
	}
}

/*****
ugrás a paraméterül kapott sorszámú frame-re
*****/
void Scene::JumpToFrame(size_t FrameNumber_in)
{
	if( FrameNumber_in < Frames.size() )
	{
		IndexOfCurrentFrame = FrameNumber_in;
		Finished = false;
	}
}



/*****
konstruktor
*****/
DrawableComponent::DrawableComponent(GameObject *OwnerGameObject_in) : Component(OwnerGameObject_in), CurrentFrame(NULL)
{
	Clear();
}

/*****
A komponens inicializálása / alapállapotba hozása
*****/
void DrawableComponent::Clear()
{
	TextureID = 0;
	CoordinateSpace = WORLD_SPACE;
	CurrentFrame	= NULL;
	FlippedHorizontally = FlippedVertically = false;
	Width = Height = 0;
	Position.x = Position.y = 0;

	Scenes.clear();
	IndexOfCurrentScene = 0;								// fontos, hogy valójában NINCS egyetlen scene sem az objektumban, tehát ezt ellenőrizni kell a Scenes vektor indexelésekor
	Stopped = false;
}

/*****
a legfontosabb értékek beállítása egyetlen függvény segítségével
*****/
void DrawableComponent::Set(float Width_in, float Height_in, sf::Vector2f Position_in, size_t TextureID_in, COORDINATE_SPACE CoordinateSpace_in, bool FlippedHorizontally_in, bool FlippedVertically_in, bool Stopped_in)
{
	Width = Width_in;
	Height = Height_in;
	Position = Position_in;
	TextureID = TextureID_in;
	CoordinateSpace = CoordinateSpace_in;
	FlippedHorizontally = FlippedHorizontally_in;
	FlippedVertically = FlippedVertically_in;
	Stopped = Stopped_in;
}

/*****
animált sprite létrehozása egy lépésben
*****/
void DrawableComponent::CreateAnimatedSprite(unsigned NumberOfRows_in, unsigned NumberOfColumns_in, float Duration_in, Scene::ACTION OnLastSceneFinished_in)
{
	// egy frame ekkora részt használ a textúrából
	float frame_s = 1.f / NumberOfColumns_in;
	float frame_t = 1.f / NumberOfRows_in;

	// egy scene-re jutó idő
	float scene_duration = Duration_in / NumberOfRows_in;

	// minden sor egy scene lesz
	Scene scene;
	Frame frame;
	for( unsigned row = 0; row < NumberOfRows_in; row++ )
	{
		// egy soron belül az oszlopok bejárása, ezek lesznek az adott scene frame-jei
		scene.Clear();
		scene.SetDuration(scene_duration);
		scene.SetFinished(false);
		scene.SetOnFinish((row == NumberOfRows_in - 1) ? OnLastSceneFinished_in : Scene::NEXT_SCENE);

		for( unsigned column = 0; column < NumberOfColumns_in; column++ )
		{
			frame.SetTextureCoordinates(column * frame_s, 1 - ((row+1) * frame_t), (column+1) * frame_s, 1 - row * frame_t);
			scene.AddFrame(frame);
		}

		AddScene(scene);
	}

	JumpToScene(0);
}

/*****
scene elérése: pointert ad vissza a paraméterül kapott indexû scene-re, ha érvényes az index,
egyébként 0-t ad vissza
*****/
Scene *DrawableComponent::AccessScene(size_t Index_in)
{
	if( Index_in < Scenes.size() )
	{
		return &Scenes[Index_in];
	}
	else
	{
		return NULL;
	}
}

/*****
ugrás a megadott scene megadott frame-ére
*****/
void DrawableComponent::JumpToScene(size_t SceneNumber_in, size_t FrameNumber_in)
{
	if( SceneNumber_in < Scenes.size() )
	{
		IndexOfCurrentScene = SceneNumber_in;
		Scenes[IndexOfCurrentScene].JumpToFrame(FrameNumber_in);
		CurrentFrame = Scenes[IndexOfCurrentScene].GetCurrentFramePointer();
		Scenes[IndexOfCurrentScene].SetFinished(false);
	}
}

/*****
üzenet fogadása
*****/
void DrawableComponent::ReciveMessage(const Message &msg)
{
	switch (msg.MessageType) {
		case LOCATION_CHANGED:
			this->Position = sf::Vector2f(msg.LocationChangedMessage.Left,msg.LocationChangedMessage.Bottom)+RelativePositionFromHitbox;
			break;
		case SET_ANIMATION_STATE_MESSAGE_TYPE:
			if ( msg.SetAnimationStateMessage.animation >= 0 )
			this->JumpToScene( msg.SetAnimationStateMessage.animation);
			this->SetFlipped( msg.SetAnimationStateMessage.FlipHorizontal , false );
			break;
	}

}

/*****
komponens frissítése
*****/
void DrawableComponent::Update()
{
	// ha üres a Scenes vektor, egyelőre használhatatlan a sprite
	if( Scenes.size() == 0 )
	{
		return;
	}

	// ha el van indítva az animáció, és tartalmaz is legalább egy jelenetet a sprite, akkor frissítünk
	if( (!Stopped) )
	{
		// ha az aktuális scene a végére ért...
		if( Scenes[IndexOfCurrentScene].GetFinished() )
		{
			// mi a teendő a scene végének elérésekor?
			switch( Scenes[IndexOfCurrentScene].GetOnFinish() )
			{
				// scene ismétlése
				case Scene::REPEAT_SCENE :
				{
					JumpToScene(IndexOfCurrentScene);
					break;
				}

				// következő scene-re ugrás
				case Scene::NEXT_SCENE :
				{
					// ha ez volt az utolsó scene, ugrás a legelsõre
					JumpToScene((IndexOfCurrentScene == Scenes.size() - 1) ? 0 : IndexOfCurrentScene + 1);
					break;
				}

				// animáció leállítása (szüneteltetése...)
				case Scene::STOP_PLAYING :
				{
					Stopped = true;
					break;
				}
			}
		}
		// még nincs a scene végén
		else
		{
			Scenes[IndexOfCurrentScene].Update(20);
		}
	}

	// pointer lekérése, amely az aktuális frame-re mutat; ez kell a rendereléshez
	CurrentFrame = Scenes[IndexOfCurrentScene].GetCurrentFramePointer(); 
}

/*****
komponens megjelenítése
*****/
void DrawableComponent::Draw()
{
	// ha nincs scene / üres a scene, nem rajzol semmit
	if( CurrentFrame == NULL )
	{
		return;
	}

	// textúra kötése
	TextureManager::Instance().BindTexture(TextureID);

	// modellnézeti mátrix elmentése a verembe
	glPushMatrix();

	// ha screen-space-ben van, egységmátrix betöltése
	if( CoordinateSpace == SCREEN_SPACE )
	{
		glLoadIdentity();
	}

	// sprite elhelyezése a megfelelő helyen
	glTranslatef(Position.x, Position.y, 0);

	// textúrakoordinátákra mutató pointerek létrehozása a sprite tükrözöttségének megfelelõen
	float *lower_left, *lower_right, *upper_left, *upper_right;

	// ha vízszintesen tükrözve van
	if( FlippedHorizontally )
	{
		// és függõlegesen is tükrözve van
		if( FlippedVertically )
		{
			lower_left  = CurrentFrame->TCUpperRight;
			lower_right = CurrentFrame->TCUpperLeft;
			upper_right = CurrentFrame->TCLowerLeft;
			upper_left  = CurrentFrame->TCLowerRight;
		}
		// de függõlegesen nincs tükrözve
		else
		{
			lower_left  = CurrentFrame->TCLowerRight;
			lower_right = CurrentFrame->TCLowerLeft;
			upper_right = CurrentFrame->TCUpperLeft;
			upper_left  = CurrentFrame->TCUpperRight;
		}
	}
	// ha vízszintesen nincs tükrözve
	else
	{
		// de függõlegesen tükrözve van
		if( FlippedVertically )
		{
			lower_left  = CurrentFrame->TCUpperLeft;
			lower_right = CurrentFrame->TCUpperRight;
			upper_right = CurrentFrame->TCLowerRight;
			upper_left  = CurrentFrame->TCLowerLeft;
		}
		// és függõlegesen sincs tükrözve
		else
		{
			lower_left  = CurrentFrame->TCLowerLeft;
			lower_right = CurrentFrame->TCLowerRight;
			upper_right = CurrentFrame->TCUpperRight;
			upper_left  = CurrentFrame->TCUpperLeft;
		}
	}
	
	// renderelés
	glBegin(GL_QUADS);
		glTexCoord2fv(lower_left);
		glVertex2d(0, 0);
		glTexCoord2fv(lower_right);
		glVertex2d(Width, 0);
		glTexCoord2fv(upper_right);
		glVertex2d(Width, Height);
		glTexCoord2fv(upper_left);
		glVertex2d(0, Height);
	glEnd();

	// modellnézeti mátrix visszatöltése a verembõl
	glPopMatrix();
}
