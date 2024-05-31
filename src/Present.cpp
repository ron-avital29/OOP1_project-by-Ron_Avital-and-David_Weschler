#include "Present.h"

#include <iostream>	//debugging

Present::Present(sf::Texture* aTexture)
	: StaticObj(aTexture)
{}

void Present::handleCollision(Base& unknownObj) 
{
	unknownObj.handleCollision(*this);
}

void Present::handleCollision(Mouse& theMouse) 
{
	theMouse.handleCollision(*this);
}