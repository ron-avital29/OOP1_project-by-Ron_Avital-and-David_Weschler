#include "Base.h"

Base::Base(sf::Texture* aTexture)
{
	m_texture = aTexture;
	m_sprite.setTexture(*m_texture);
	m_sprite.setPosition(m_location);
	m_sprite.setOrigin(m_sprite.getLocalBounds().getSize() / 2.f);

	m_sprite.setScale(DESIRED_SIZE / m_texture->getSize().x, DESIRED_SIZE / m_texture->getSize().y);
}

sf::Vector2f Base::getLocation() const
{
	return m_location;
}

sf::FloatRect Base::getGlobalBounds() const	
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Base::getStartLocation() const
{
	return m_startLocation;
}

sf::Vector2f Base::getOldLocation() const
{
	return m_oldLocation;
}

void Base::setTexture(sf::Texture *aTexture)
{
	m_texture = aTexture;
}

void Base::setLocation(sf::Vector2f location)
{
	m_oldLocation = m_location;
	m_location = location;
}

void Base::setStartLocation()
{
	m_startLocation = m_location;
}

void Base::setDrawSettings(int posRow, int posCol)
{
	auto x = float(DESIRED_SIZE * posCol)+15;
	auto y = float(DESIRED_SIZE * posRow)+15;

	setLocation(sf::Vector2f(x, y));
	m_oldLocation = m_location;
	setStartLocation();
}

bool Base::checkCollision(Base& unknownObj) const 
{
	auto overLapping = 0.2f;
	auto sizeDecrese = 1.4;

	sf::FloatRect bounds[2];
	bounds[0] = m_sprite.getGlobalBounds();
	bounds[1] = unknownObj.getGlobalBounds();

	for (int i = 0; i < 2; i++)
	{
		bounds[i].left += bounds[i].width * overLapping;
		bounds[i].top += bounds[i].height * overLapping;
		bounds[i].width /= (sizeDecrese);
		bounds[i].height /= (sizeDecrese);
	}
	return bounds[0].intersects(bounds[1]);
}

void Base::drawObj(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_location);
	window.draw(m_sprite);
}