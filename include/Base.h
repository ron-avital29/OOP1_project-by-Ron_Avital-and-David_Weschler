#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Singleton.h"
#include <iostream>

class Wall;
class Cheese;
class Key;
class Present;
class Door;
class Cat;
class Mouse;

class Base
{
public:
	Base(sf::Texture* aTexture);
	virtual ~Base() {};

	sf::Vector2f getLocation() const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getStartLocation() const;
	sf::Vector2f getOldLocation() const;

	void setTexture(sf::Texture *aTexture);
	void setLocation(sf::Vector2f location);
	void setStartLocation();
	void setDrawSettings(int posRow, int posCol);

	bool checkCollision(Base& unknownObj) const;

	virtual void handleCollision(Base& unknownObj) = 0;
	virtual void handleCollision(Mouse& theMouse) {};
	virtual void handleCollision(Wall& wall) {};
	virtual void handleCollision(Door& door) {};
	virtual void handleCollision(Key& key) {};
	virtual void handleCollision(Present& present) {};
	virtual void handleCollision(Cheese& cheese) {};
	virtual void handleCollision(Cat& cat) {};

	void drawObj(sf::RenderWindow& window);

protected:		
	
	sf::Texture *m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_location;
	sf::Vector2f m_oldLocation;
	sf::Vector2f m_startLocation;
};