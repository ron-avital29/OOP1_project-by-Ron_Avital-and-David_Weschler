#include "Door.h"
#include "Mouse.h"
#include "Cat.h"

Door::Door(sf::Texture* aTexture)
	: StaticObj(aTexture)
{}

void Door::handleCollision(Base& unknownObj)
{
	unknownObj.handleCollision(*this);
}

void Door::handleCollision(Mouse& theMouse)
{
	theMouse.handleCollision(*this);
}

void Door::handleCollision(Cat& cat)
{
	cat.handleCollision(*this);
}
