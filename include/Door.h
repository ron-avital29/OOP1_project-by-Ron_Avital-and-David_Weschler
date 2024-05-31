#pragma once

#include "StaticObj.h"

class Door : public StaticObj
{
public:
	Door(sf::Texture* aTexture);
	virtual ~Door() {};

	virtual void handleCollision(Base& unknownObj);
	virtual void handleCollision(Mouse& theMouse);
	virtual void handleCollision(Cat& cat);

private:
};