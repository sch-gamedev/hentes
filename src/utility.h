/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _UTILITY_H_
#define _UTILITY_H_


namespace Utility {

	enum DIRECTION
	{
	LEFT,
	TOP,
	RIGHT,
	BOTTOM,
	NONE
	};
	
	DIRECTION OpositeDirection (DIRECTION dir);
	
	template<class T>
	class MarkedAsDeletedPred {
	public:
		bool operator() (T* t) {
			return t->IsMarkedAsDeleted();
		}
	}; 
}
#endif //_UTILITY_H_