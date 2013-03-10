/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _COLOR_H_
#define _COLOR_H_


struct sColor4
{
	float R, G, B, A;

	sColor4(float R = 1, float G = 1, float B = 1, float A = 1) : R(R), G(G), B(B), A(A)
	{
	}
};

#endif
