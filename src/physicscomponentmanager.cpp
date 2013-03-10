/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "physicscomponentmanager.h" 

bool PhysicsComponentManager::QueuedMessage::operator==(const QueuedMessage& QueuedMessage_in)
{
	
	return (this->Component1 == QueuedMessage_in.Component1 || this->Component1 == QueuedMessage_in.Component2) 
		&& (this->Component2 == QueuedMessage_in.Component1 || this->Component2 == QueuedMessage_in.Component2);
}

void PhysicsComponentManager::addQueuedMessage(QueuedMessage Msg) 
{
	for ( std::vector<QueuedMessage>::iterator it = QueuedMessages.begin(); it != QueuedMessages.end(); ++ it ) 
	{
		if ( *it == Msg ) {
			if ( (*it).Direction == Utility::NONE || Msg.Direction == Utility::TOP || Msg.Direction == Utility::BOTTOM ) {
				if ( it->Component1 == Msg.Component1 )
					it->Direction = Msg.Direction;	
				else
					it->Direction = Utility::OpositeDirection(Msg.Direction);
			} 
			return;
		}
	} 
	QueuedMessages.push_back(Msg);
}

PhysicsComponentManager::QueuedMessage::QueuedMessage(PhysicsComponent* a, PhysicsComponent* b, Utility::DIRECTION Direction, sf::Vector2f collPt) 
{
	this->Component1 = a;
	this->Component2 = b;
	this->Direction = Direction;
	this->collisionPoint = collPt;
}

void PhysicsComponentManager::Update() 
{
	RemoveMarkedComponents();
	QueuedMessages.clear();

	// Végigmegyünk az összes elemenén és feldolgozzuk a mozgási szándékukat, illetve megnézzük hogy érintkezett-e valakivel
	for ( std::list<PhysicsComponent*>::iterator it = Components.begin(); it!= Components.end(); ++it)
	{
		// (*it) helyett a-t hyasználunk
		PhysicsComponent* a = *it;

		// Ha nem mozog és nem esik akkor nem foglalkozunk vele:
		if ( a->MovementIntent == sf::Vector2f() && !a->Gravity && a->FallingVelocity == 0.0f )
		{
			continue;
		}

		// Ha hat az objektumra a gravitáció, akkor növeljük az esése sebességét
		if ( a->Gravity )
		{
			a->FallingVelocity -= this->GravityPower;
		}

		// Kiszámítjuk, hogy hova szeretne menni az objektum.
		sf::Vector2f destination = a->LeftBottomCorner + a->MovementIntent + sf::Vector2f(0.0f,a->FallingVelocity);

		// Ha mozogni próbál és van Solid éle, akkor ütközést vizsgálunk
		if (a->Solid[0] || a->Solid[1] || a->Solid[2] || a->Solid[3])
		{
			// Megvizsgáljuk, hogy melyik objektumokkal ütközött, és ezek milyen módon tartják fel a mozgását
			for(std::list<PhysicsComponent*>::iterator it2 = Components.begin(); it2!=Components.end(); ++it2)
			{
				PhysicsComponent* b = *it2;

				if ( b == a )
				{
					continue;
				}

				// Ha egy objektum semelyik oldala sem Solid, akkor biztosan nem tartja fel a mozgásunkat
				if ( !(b->Solid[0] || b->Solid[1] || b->Solid[2] || b->Solid[3]))
				{
					continue;
				}

				// <Az egyes oldalak páronkénti vizsgálata>
				// it2 : RIGHT
				if (a->LeftBottomCorner.x		>=	b->LeftBottomCorner.x + b->Size.x	&&
					destination.x				<	b->LeftBottomCorner.x + b->Size.x	&&
					destination.y				<	b->LeftBottomCorner.y + b->Size.y	&&
					destination.y + a->Size.y	>	b->LeftBottomCorner.y				&&
					a->Solid[Utility::LEFT] &&
					b->Solid[Utility::RIGHT])
				{
					addQueuedMessage(QueuedMessage(a,b,Utility::LEFT, b->LeftBottomCorner));
					destination.x = b->LeftBottomCorner.x + b->Size.x;
				}

				// it2 : LEFT
				if (a->LeftBottomCorner.x + a->Size.x	<=	b->LeftBottomCorner.x				&&
					destination.x + a->Size.x			>	b->LeftBottomCorner.x				&&
					destination.y						<	b->LeftBottomCorner.y + b->Size.y	&&
					destination.y + a->Size.y			>	b->LeftBottomCorner.y				&&
					a->Solid[Utility::RIGHT] &&
					b->Solid[Utility::LEFT])
				{
					addQueuedMessage(QueuedMessage(a,b,Utility::RIGHT, b->LeftBottomCorner));
					destination.x = b->LeftBottomCorner.x - a->Size.x;
				}

				// it2 : TOP
				if (a->LeftBottomCorner.y		>=	b->LeftBottomCorner.y + b->Size.y	&&
					destination.y				<	b->LeftBottomCorner.y + b->Size.y	&&
					destination.x				<	b->LeftBottomCorner.x + b->Size.x	&&
					destination.x + a->Size.x	>	b->LeftBottomCorner.x				&&
					a->Solid[Utility::BOTTOM] &&
					b->Solid[Utility::TOP]) 
				{
					a->FallingVelocity = 0.0f;
					addQueuedMessage(QueuedMessage(a,b,Utility::BOTTOM, b->LeftBottomCorner));
					destination.y = b->LeftBottomCorner.y + b->Size.y;
				}

				// it2 : Bottom
				if (a->LeftBottomCorner.y + a->Size.y	<=	b->LeftBottomCorner.y				&&
					destination.y + a->Size.y			>	b->LeftBottomCorner.y				&&
					destination.x						<	b->LeftBottomCorner.x + b->Size.x	&&
					destination.x + a->Size.x			>	b->LeftBottomCorner.x				&&
					a->Solid[Utility::TOP] &&
					b->Solid[Utility::BOTTOM]) 
				{
					a->FallingVelocity = 0.0f;
					addQueuedMessage(QueuedMessage(a,b,Utility::TOP, b->LeftBottomCorner));
					destination.y = b->LeftBottomCorner.y - a->Size.y;
				}
				// </Az egyes oldalak páronkénti vizsgálata>
			}	
			// Beálítjuk az új helyet és erről értesítjük a physics objektumot
		}

		a->LocationChanged(destination);
		a->MovementIntent = sf::Vector2f();

		//Megnézzük, hogy valakivel érintkezik-e a mozgás végén
		for(std::list<PhysicsComponent*>::iterator it3 = Components.begin(); it3 != Components.end(); ++it3) 
		{
			PhysicsComponent* b = *it3; // PhysicsComponent 

			if ( b == a )
			{
				continue;
			}

			// Megvizsgálja, hogy a 2 téglalap érinthezik-e egymással
			if (a->GetLeftBottomCorner().x	<= b->GetLeftBottomCorner().x + b->GetSize().x &&
				b->GetLeftBottomCorner().x	<= a->GetLeftBottomCorner().x + a->GetSize().x &&
				a->GetLeftBottomCorner().y	<= b->GetLeftBottomCorner().y + b->GetSize().y &&
				b->GetLeftBottomCorner().y	<= a->GetLeftBottomCorner().y + a->GetSize().y)
			{
				addQueuedMessage(QueuedMessage(a,b,Utility::NONE, a->GetLeftBottomCorner() + a->GetSize() * 0.5f));
			}
		}
	}

	// Kiküldjük az ütközések üzeneteit
	for ( std::vector<QueuedMessage>::iterator msgIt = QueuedMessages.begin(); msgIt != QueuedMessages.end(); ++msgIt ) 
	{
		msgIt->Component1->Collide(msgIt->Component2,msgIt->Direction, msgIt->collisionPoint);
		msgIt->Component2->Collide(msgIt->Component1,Utility::OpositeDirection(msgIt->Direction), msgIt->collisionPoint);
	}
}