#pragma once

#include "StaticObj.h"

class Cheese : public StaticObj
{
public:
	Cheese(sf::Texture* aTexture);
	virtual ~Cheese() {};

	virtual void handleCollision(Base& unknownObj) {};
	virtual void handleCollision(Mouse& theMouse);
	virtual void handleCollision(Cat& cat) {};

private:	
};