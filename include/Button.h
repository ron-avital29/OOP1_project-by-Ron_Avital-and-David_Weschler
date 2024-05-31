#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(sf::Vector2f location, int code, sf::Texture *aTexture);

	sf::FloatRect getGlobalBound() const;
	int getCode() const;

	void setTexture(const sf::Texture *aTexture);
	void setScale(float x, float y);

	void drawButton(sf::RenderWindow& window) const;

private:
	sf::CircleShape m_shape;
	sf::Vector2f m_location;

	int m_code;
};