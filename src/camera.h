/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SFML/System/Vector2.hpp>

class Camera
{
public :
	sf::Vector2f position;					// a kamera poz�ci�ja vil�gkoordin�tat�rben

	// konstruktor
	Camera(sf::Vector2f position_in);
	Camera();

	// kamera elhelyez�se
	void Look();
};

#endif
