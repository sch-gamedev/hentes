/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include <SFML/OpenGL.hpp>
#include "texturemanager.h"
#include "particle.h"

// a részecske kirajzolása
void cParticle::render()
{
	// szín és textúra alkalmazása
	glColor4d(color.R, color.G, color.B, color.A);
	TextureManager::Instance().BindTexture(textureIndex);
	const Texture *texture = TextureManager::Instance().GetTexturePointer(textureIndex);

	glPushMatrix();
	glTranslatef(position.x, position.y, 0.f);
	glRotatef(rotation, 0, 0, 1);

	float half_size = size / 2.f;
	float texture_portion_unit = 1.f / numberOfTexturePortions;

	glBegin(GL_QUADS);
		glTexCoord2f(texturePortionIndex * texture_portion_unit, 0);
		glVertex2f(-half_size, -half_size);
		glTexCoord2f((texturePortionIndex+1) * texture_portion_unit, 0);
		glVertex2f(half_size, -half_size);
		glTexCoord2f((texturePortionIndex+1) * texture_portion_unit, 1);
		glVertex2f(half_size, half_size);
		glTexCoord2f(texturePortionIndex * texture_portion_unit, 1);
		glVertex2f(-half_size, half_size);
	glEnd();

	glPopMatrix();
}
