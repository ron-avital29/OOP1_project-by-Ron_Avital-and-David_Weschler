#include "Button.h"
#include <iostream>

Button::Button(sf::Vector2f location, int code, sf::Texture *aTexture)
	:m_location(location), m_code(code)
{	
	m_shape.setRadius(100);
	m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
	m_shape.setPosition(m_location);
	m_shape.setTexture(aTexture);
}

sf::FloatRect Button::getGlobalBound() const
{
	return m_shape.getGlobalBounds();
}

int Button::getCode() const
{
	return m_code;
}

void Button::setTexture(const sf::Texture* aTexture)
{
	m_shape.setTexture(aTexture);
}

void Button::setScale(float x, float y)
{
	m_shape.setScale(x, y);
}

void Button::drawButton(sf::RenderWindow& window) const
{
	window.draw(m_shape);
}