#pragma once

#include "Animal.h"
#include <SFML/Graphics.hpp>

const int POSSIBLE_DIR = 4;

class Cat : public Animal
{
public:
	Cat(sf::Texture* aTexture);
	virtual ~Cat() {};
	
	bool getCrazy() const;

	void setCrazy();
	void setDestination(sf::Vector2f location);
	virtual void setColor(bool state);

	virtual void handleCollision(Base& unknownObj);
	virtual void handleCollision(Mouse& theMouse);
	virtual void handleCollision(Wall& wall);
	virtual void handleCollision(Door& door);
	virtual void handleCollision(Key& key) {};
	virtual void handleCollision(Present& present) {};
	virtual void handleCollision(Cheese& cheese) {};
	virtual void handleCollision(Cat& cat);

	virtual void move(sf::Time deltaTime);

private:
	sf::Vector2f m_destination;
	sf::Time m_scaleTime;

	bool m_isCrazy;
	bool m_isLeft;
};