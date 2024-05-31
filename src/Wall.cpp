#include "Wall.h"

Wall::Wall(sf::Texture* aTexture)
	: StaticObj(aTexture)
{}

void Wall::handleCollision(Base& unknownObj)
{
	unknownObj.handleCollision(*this);
}

void Wall::handleCollision(Mouse& theMouse)
{
	theMouse.handleCollision(*this);	
}

void Wall::handleCollision(Cat& aCat)
{
	aCat.handleCollision(*this);
}
