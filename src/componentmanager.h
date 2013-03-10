/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#ifndef _COMPONENTMANAGER_H_
#define _COMPONENTMANAGER_H_

#include <list>
#include <vector>

/*****
Komponens managerek absztrakt ősosztálya
*****/
template<class T>
class ComponentManager
{
protected :
	std::list<T*> Components;													// a beregisztrált komponensek listája
	std::vector<T*> DeletedComponents;
	virtual void RemoveMarkedComponents() 
	{
		DeletedComponents.clear();
		for( std::list<T*>::iterator it = Components.begin(); it != Components.end(); ++it) 
			if ((*it)->IsMarkedAsDeleted()) DeletedComponents.push_back(*it);	
		Components.remove_if(Utility::MarkedAsDeletedPred<T>());
		for ( std::vector<T*>::iterator it = DeletedComponents.begin(); it != DeletedComponents.end(); ++it) if ( !((*it)->ShouldRemoveWithoutDeleting()) ) delete *it;
	}

public:
	// komponens hozzáadása a managerhez
	void RegisterComponent(T *ComponentPtr_in)
	{
		// pointer hozzáadása
		Components.push_back(ComponentPtr_in);
		// semmiképp ne lehessen többször hozzáadni ugyanazt...
		Components.unique();
	}

	// komponens eltávolítása
	void UnRegisterComponent(T *ComponentPtr_in)
	{
		Components.remove(ComponentPtr_in);
	}

	// összes komponens eltávolítása
	void UnRegisterAllComponents()
	{
		Components.clear();
	}

	// összes komponens frissítése
	virtual void Update() = 0;
};


#endif
