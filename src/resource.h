/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>


/*****
Er�forr�sok absztrakt �soszt�lya
*****/
class Resource
{
protected :
	std::string ID;													// az er�forr�s azonos�t�ja (legt�bbsz�r f�jln�v)
	

public :
	// az er�forr�s felszabad�t�sa
	virtual void Destroy(void) = 0;

	// elen�rz�s, hogy van-e bet�ltve valami
	virtual bool Loaded(void) const = 0;

	// az er�forr�s azonos�t�j�nak lek�rdez�se
	std::string GetID(void) const
	{
		return ID;
	}
};

#endif
