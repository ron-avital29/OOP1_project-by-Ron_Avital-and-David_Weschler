#pragma once

#include "Base.h"

class Animal : public Base
{
public:
	Animal(sf::Texture* aTexture);

	virtual ~Animal() {};

	virtual void move(sf::Time deltaTime) = 0;
	virtual void setColor(bool state) = 0;
	virtual void handleCollision(Base& unknownObj) = 0;
	virtual void handleCollision(Mouse& theMouse) = 0;
	virtual void handleCollision(Wall& wall) = 0;
	virtual void handleCollision(Door& door) = 0;
	virtual void handleCollision(Key& key) = 0;
	virtual void handleCollision(Present& present) = 0;
	virtual void handleCollision(Cheese& cheese) = 0;
	virtual void handleCollision(Cat& cat) = 0;

protected:
	sf::Sound m_sound;
	float m_speed;
};