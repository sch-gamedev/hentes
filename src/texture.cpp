/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include <SFML/Graphics/Image.hpp>
#include "texture.h"


/*****
A megadott el�r�si �tvonalon tal�lhat� k�pf�jlt megnyitja, bet�lti, �s a tartalm�b�l text�r�t k�sz�t.
Opcion�lisan t�kr�zheti a k�pet, k�sz�thet mipmap list�t.
A visszat�r�si �rt�k 0, ha sikeres volt a bet�lt�s, ellenkez� esetben egy hibak�d.
*****/
int Texture::Create(const std::string Filename_in, bool Mipmapping_in, bool Flip_in, GLint WrapS_in, GLint WrapT_in)
{
	// a f�jln�v nem lehet �res string; �res text�r�t egy m�sik f�ggv�nnyel lehet l�trehozni
	if( Filename_in == "" )
	{
		return 1;
	}

	// a f�jl bet�lt�se
	sf::Image image;
	if( image.loadFromFile(Filename_in) == false )
	{
		return 2;	// a f�jl nem tal�lhat� / nem olvashat� be
	}

	this->ID = Filename_in;
	
	// t�kr�z�s, ha sz�ks�ges
	if( Flip_in )
	{
		image.flipVertically();
	}

	// adatok lek�rdez�se
	Width  = image.getSize().x;
	Height = image.getSize().y;

	// OpenGL azonos�t� l�trehoz�sa
	glGenTextures(1, &GLID);

	// text�ra OpenGL k�t�se
	Bind();

	// text�ra param�terek be�ll�t�sa (a filterbe�ll�t�sok att�l f�ggenek, hogy van-e mipmapping)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapS_in);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapT_in);

	// text�ra l�trehoz�sa mipmappinggel
	if( Mipmapping_in )
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Width, Height,GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.getPixelsPtr());
	}
	else // nincs mipmapping
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.getPixelsPtr());
	}

	// ellen�rz�s, hogy t�rt�nt-e OpenGL hiba
	if( glGetError() != GL_NO_ERROR )
	{
		return 3;		// OpenGL error
	}

	return 0;
}
