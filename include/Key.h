#pragma once

#include "StaticObj.h"
#include "Mouse.h"

class Key : public StaticObj
{
public:
	Key(sf::Texture* aTexture);
	virtual ~Key() {};

	virtual void handleCollision(Base& unknownObj);
	virtual void handleCollision(Mouse& theMouse);
	virtual void handleCollision(Cat& cat) {};

private:
};