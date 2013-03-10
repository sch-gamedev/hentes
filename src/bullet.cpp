/* Copyright (C) 2012 KSZK GameDev
 * For conditions of distribution and use, see copyright notice in main.cpp
 */
#include "bullet.h"
#include "gameobject.h"
#include "spriteconfigmanager.h"

Bullet::Bullet() 
{

	this->inUse = false;
	this->gameObject = new GameObject();
	this->bulletLogicComponent = new BulletLogicComponent(this->gameObject,this);
	this->physicsComponent = new PhysicsComponent(this->gameObject,sf::Vector2f(),sf::Vector2f(32.f,16.f),false,false);
	this->drawableComponent = new DrawableComponent(this->gameObject);
	SpriteConfig sc = SpriteConfigManager::Instance()->LookupSpriteConfig("BULLETS_SPRITE_ID");
	this->drawableComponent->Set(32.f, 16.f, sf::Vector2f(), sc.textureId, DrawableComponent::WORLD_SPACE);
	this->drawableComponent->CreateAnimatedSprite(sc.rows, sc.columns, sc.duration, Scene::REPEAT_SCENE);

	for( unsigned i=0; i< sc.rows; i++)
	{
		this->drawableComponent->AccessScene(i)->SetOnFinish(Scene::REPEAT_SCENE);
	}

	this->gameObject->AddComponent(this->bulletLogicComponent);
	this->gameObject->AddComponent(this->physicsComponent);
	this->gameObject->AddComponent(this->drawableComponent);
}

Bullet::~Bullet() 
{
	delete this->gameObject;
	delete this->bulletLogicComponent;
	delete this->physicsComponent;
	delete this->drawableComponent;
}

void Bullet::RemoveIfUsed() 
{
	if ( this->inUse ) 
	{
		this->bulletLogicComponent->MarkAsDeleted(true);
		this->physicsComponent->MarkAsDeleted(true);
		this->drawableComponent->MarkAsDeleted(true);
		inUse = false;
	}
}