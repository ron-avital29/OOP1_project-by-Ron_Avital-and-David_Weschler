#include "Cheese.h"
#include "Mouse.h"

Cheese::Cheese(sf::Texture* aTexture) 
	: StaticObj(aTexture)
{}

void Cheese::handleCollision(Mouse& theMouse)
{
	theMouse.handleCollision(*this);
}
