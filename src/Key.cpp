#include "Key.h"

Key::Key(sf::Texture* aTexture)
	: StaticObj(aTexture)
{}

void Key::handleCollision(Base& unknownObj)
{
	unknownObj.handleCollision(*this);
}

void Key::handleCollision(Mouse& theMouse)
{
	theMouse.handleCollision(*this);
}
