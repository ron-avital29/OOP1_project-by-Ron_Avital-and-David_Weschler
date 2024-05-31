#include "Cat.h"
#include <cstdlib>
#include <Door.h>
#include <Wall.h>

Cat::Cat(sf::Texture* aTexture)
	: Animal(aTexture)
{
	m_speed = 50.f;
	m_isCrazy = m_isLeft = false;
	m_destination.x = m_destination.y = 0;
}

bool Cat::getCrazy() const
{
	return m_isCrazy;
}

void Cat::setCrazy()
{
	m_isCrazy = !m_isCrazy;

	if (m_isCrazy)
	{
		m_destination.x = rand() % 900;
		m_destination.y = rand() % 800;
	}
}

void Cat::setDestination(sf::Vector2f location)
{
	m_destination = location;
}

void Cat::setColor(bool state)
{
	m_sprite.setColor((state) ? sf::Color(102, 102, 255) : sf::Color(255, 255, 255));
}

void Cat::handleCollision(Base& unknownObj)
{
	unknownObj.handleCollision(*this);
}

void Cat::handleCollision(Mouse& theMouse)
{
	theMouse.handleCollision(*this);
}

void Cat::handleCollision(Wall& wall)
{
	setCrazy();
	m_location = m_oldLocation;
	m_sprite.move(m_location);
}

void Cat::handleCollision(Door& door)
{
	setCrazy();
	m_location = m_oldLocation;
	m_sprite.move(m_location);
}

void Cat::handleCollision(Cat& cat)
{	
	m_sound.setBuffer(Singleton::instance().getSoundBuffer(CAT_SOUND));
	m_sound.play();	
}

void Cat::move(sf::Time deltaTime)
{
	sf::Vector2f direction = m_destination - m_location;
	float distanceToMouse = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	float newDistance;
	double best_distance = 0;
	bool moveNotGood = false;

	int cor_x[] = { 0, 0, 1, -1 };
	int cor_y[] = { -1, 1, 0, 0 };

	sf::Vector2f best(m_location);
	for (int i = 0; i < POSSIBLE_DIR; i++)
	{
		sf::Vector2f test(m_location.x + cor_x[i], m_location.y + cor_y[i]);

		sf::Vector2f Newdirection = m_destination - test;
		newDistance = std::sqrt(Newdirection.x * Newdirection.x + Newdirection.y * Newdirection.y);

		if (newDistance <= distanceToMouse)
		{
			if (best_distance == 0 || newDistance < best_distance)
			{
				best_distance = newDistance;
				best = test;
			}
		}
	}

	if (best_distance != 0)
	{
		m_oldLocation = m_location;
		sf::Vector2f movement = (best - m_location) * m_speed * deltaTime.asSeconds();
		m_location += movement;

		if ((m_location.x > m_oldLocation.x) && m_isLeft)
		{
			m_sprite.scale(-1, 1);
			m_isLeft = false;
		}
		else if ((m_location.x < m_oldLocation.x) && !m_isLeft)
		{
			m_sprite.scale(-1, 1);
			m_isLeft = true;
		}
	}

	if (newDistance < 10)
	{
		setCrazy();
	}
}