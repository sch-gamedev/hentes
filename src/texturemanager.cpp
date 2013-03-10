/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "texturemanager.h"


/*****
TextureManager private konstruktora.
*****/
TextureManager::TextureManager()
{
	// text�r�kat t�rol� vektor inicializ�l�sa
	NumberOfTextures = TEXTURES_INITIAL_SIZE;
	Textures.clear();
	for( size_t i = 0; i < NumberOfTextures; i++ )
	{
		Textures.push_back(new Texture());
	}

	// nincs bet�lt�tt text�ra
	NumberOfLoadedTextures = 0;

	// er�forr�skezel� inicializ�l�sa
	Clear();
}

/*****
Az er�forr�skezel� rendszer inicializ�l�sa.
*****/
void TextureManager::Clear()
{
	// nincs akt�v text�ra
	ActiveTexture = Textures.size();
}

/*****
GetTextureIndex - a megadott f�jln�v (egyedi azonos�t�) alapj�n
megkeresi a _bet�lt�tt_ text�ra index�t a vektorban.
A visszat�r�si �rt�k jelzi, hogy a text�ra megtal�lhat�-e (true), vagy sem (false).
A m�sodik param�terben �tadott v�ltoz� t�rolja el a megtal�lt text�ra index�t.
*****/
bool TextureManager::GetTextureIndex(const std::string &ID_in, size_t &Index_out) const
{
	for( register size_t i = 0; i < NumberOfTextures; i++ )
	{
		if( (Textures[i]->Loaded()) && (Textures[i]->GetID() == ID_in) )
		{
			Index_out = i;
			return true;
		}
	}
	return false;
}

/*****
Text�ra bet�lt�se.
Az er�forr�skezel� rendszer el�bb ellen�rzi, hogy a text�ra be van-e m�r t�ltve, �s amennyiben nem, megpr�b�lja bet�lteni.
A f�ggv�ny visszat�r�si �rt�ke megegyezik a Texture::Create met�dus��val, azt jelzi, hogy sikeres volt-e a text�ra bet�lt�se.
A param�terlista egy kiv�tellel megegyezik a Texture oszt�ly Create met�dus��val. A m�sodik param�terben �tadott v�ltoz�
kapja meg a bet�lt�tt VAGY megtal�lt text�ra index�t.
*****/
int TextureManager::LoadTexture(const std::string &Filename_in, size_t &Index_out, bool Mipmapping_in, bool Flip_in, GLint WrapS_in, GLint WrapT_in)
{
	// keres�s, hogy van-e m�r ilyen azonos�t�j�, bet�lt�tt text�ra
	size_t index;
	if( GetTextureIndex(Filename_in, index) )
	{
		// ha van, nem kell m�g egyszer bet�lteni
		Index_out = index;
		return 0;
	}

	// nincs bet�ltve a k�rt text�ra, helyet kell neki keresni a vektorban
	for( index = 0; index < NumberOfTextures; index++ )
	{
		// tal�l egy felhaszn�latlan text�ra objektumot, kil�p a ciklusb�l
		if( Textures[index]->Loaded() == false )
		{
			break;
		}
	}

	// ha az index �rt�ke az objektumok sz�ma, teli van a vektor, �t kell m�retezni
	if( index == NumberOfTextures )
	{
		NumberOfTextures += TEXTURES_INCREASE_BY;
		Textures.resize(NumberOfTextures, new Texture());
	}

	// text�ra bet�lt�se a megfelel� helyre
	Index_out  = index;
	int result = Textures[index]->Create(Filename_in, Mipmapping_in, Flip_in, WrapS_in, WrapT_in);
	// ha sikeres volt a bet�lt�s,
	if( result == 0 )
	{
		// akkor az �jonnan bet�lt�tt elem az akt�v
		ActiveTexture = index;
		// �s eggyel t�bb bet�lt�tt text�ra van
		NumberOfLoadedTextures++;
	}
	// ha nem volt sikeres a bet�lt�s, a hib�t logolja
	else
	{
		// TODO: logger oszt�ly haszn�lata itt!
		/*
		stringstream ss;
		ss << result;
		cLogger::Instance().LogError("Unable to load texture: " + Filename_in + "; errorcode: " + ss.str(), typeid(*this).name());
		*/
	}

	return result;
}
