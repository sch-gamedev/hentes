/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "texture.h"
#include <vector>
#include <sstream>

#define TEXTURES_INITIAL_SIZE 32
#define TEXTURES_INCREASE_BY  8


/*****
Textúrakezelõ osztály. Singleton.
*****/
class TextureManager
{
private :
	std::vector<Texture*>  Textures;										// textúrákat tároló vektor
	size_t				   ActiveTexture;									// a jelenleg aktív textúra indexe
	size_t				   NumberOfTextures;								// a Textures vektorban lévõ textúraobjektumok száma
	size_t				   NumberOfLoadedTextures;							// a Textures vektorban lévõ, betöltött textúrák száma

	// konstruktorok elrejtése
	TextureManager();
	TextureManager(const TextureManager &tm);

	// = operátor elrejtése
	TextureManager &operator=(const TextureManager&);

	// megállapítja, hogy a paraméterül kapott index érvényes-e, betöltött textúrára mutat-e
	bool IsValidTextureIndex(size_t Index_in)
	{
		return( (Index_in < NumberOfTextures) && (Textures[Index_in]->Loaded()) );
	}


public :
	// destruktor
	~TextureManager()
	{
		DestroyAllTextures();
	}

	// erõforráskezelõ inicializálása
	virtual void Clear();

	// példány lekérése
	static TextureManager &Instance()
	{
		static TextureManager tm;
		return tm;
	}

	// textúra megkeresése
	bool GetTextureIndex(const std::string &ID_in, size_t &Index_out) const;

	// textúra aktiválása
	bool BindTexture(size_t Index_in)
	{
		if( (ActiveTexture != Index_in) && (IsValidTextureIndex(Index_in)) )
		{
			Textures[Index_in]->Bind();
			ActiveTexture = Index_in;

			return true;
		}
		return false;
	}

	// adott indexű textúrára mutató pointer lekérdezése
	const Texture *GetTexturePointer(size_t Index_in)
	{
		return IsValidTextureIndex(Index_in) ? Textures[Index_in] : NULL;
	}

	// textúra felszabadítása
	bool DestroyTexture(size_t Index_in)
	{
		if( IsValidTextureIndex(Index_in) )
		{
			Textures[Index_in]->Destroy();
			NumberOfLoadedTextures--;
			return true;
		}
		return false;
	}

	// összes textúra felszabadítása
	void DestroyAllTextures()
	{
		for( size_t i = 0; i < NumberOfTextures; i++ )
		{
			DestroyTexture(i);
			delete Textures[i];
			Textures[i] = nullptr;
		}
	}

	// textúra betöltése
	int LoadTexture(const std::string &Filename_in, size_t &Index_out, bool Mipmapping_in = true, bool Flip_in = true, GLint WrapS_in = GL_REPEAT, GLint WrapT_in = GL_REPEAT);

	// betöltött textúrák számának lekérdezése
	size_t GetNumberOfLoadedTextures() const
	{
		return NumberOfLoadedTextures;
	}

	// Textures vektor méretének lekérdezése
	size_t GetNumberOfTextures() const
	{
		return NumberOfTextures;
	}
};

#endif
