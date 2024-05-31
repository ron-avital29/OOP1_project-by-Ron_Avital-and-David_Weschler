#pragma once

#include "StaticObj.h"
#include "Mouse.h"
#include "Cat.h"

class Wall : public StaticObj
{
public:
	Wall(sf::Texture* aTexture);
	virtual ~Wall() {};

	virtual void handleCollision(Base& unknownObj);
	virtual void handleCollision(Mouse& theMouse);
	virtual void handleCollision(Cat& aCat);

private:
};