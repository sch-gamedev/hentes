/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include <SFML/OpenGL.hpp>

#include "camera.h"

// konstruktor
Camera::Camera(sf::Vector2f position_in) : position(position_in) {}
Camera::Camera() : position(0.f, 0.f) {}

// kamera elhelyez�se
void Camera::Look()
{
	glTranslatef(-position.x, -position.y, 0.f);
}
