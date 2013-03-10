/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "resource.h"
#include <SFML/OpenGL.hpp>
#include <string>


/*****
Text�ra t�pus� er�forr�s oszt�lya
*****/
class Texture : public Resource
{
protected :
	GLuint		GLID;												// a text�raobjektum OpenGL azonos�t�ja
	unsigned	Width;												// a bet�lt�tt text�ra sz�less�ge
	unsigned	Height;												// a bet�lt�tt text�ra magass�ga

public :
	// konstruktor
	Texture()
	{
		Clear();
	}

	// destruktor
	virtual ~Texture()
	{
		Destroy();
	}

	// objektum inicializ�l�sa
	void Clear()
	{
		GLID = Width = Height = 0;
	}

	// er�forr�s felszabad�t�sa
	virtual void Destroy()
	{
		if( GLID )
		{
			glDeleteTextures(1, &GLID);
		}
		Clear();
	}

	// OpenGL azonos�t� lek�rdez�se
	GLuint GetGLID() const
	{
		return GLID;
	}

	// van-e bet�ltve text�ra
	virtual bool Loaded() const
	{
		return (GLID != 0);
	}

	// text�ra bet�lt�se f�jlb�l
	virtual int Create(const std::string Filename_in, bool Mipmapping_in = true, bool Flip_in = true, GLint WrapS_in = GL_REPEAT, GLint WrapT_in = GL_REPEAT);

	// az adott text�r�t teszi akt�vv�
	void Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, GLID);
	}

	// a text�ra felbont�s�t adja meg
	void GetResolution(double &Width_out, double &Height_out) const
	{
		Width_out  = Width;
		Height_out = Height;
	}

	// text�ra sz�less�g�vel t�r vissza
	unsigned GetWidth() const
	{
		return Width;
	}

	// a text�ra magass�g�val t�r vissza
	unsigned GetHeight() const
	{
		return Height;
	}
};

#endif
