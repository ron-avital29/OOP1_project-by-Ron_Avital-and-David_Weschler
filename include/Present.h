#pragma once

#include "StaticObj.h"
#include "Mouse.h"

class Present : public StaticObj
{
public:
	Present(sf::Texture* aTexture);
	virtual ~Present() {};

	virtual void handleCollision(Base& unknownObj);
	virtual void handleCollision(Mouse& theMouse);
	void handleCollision(Cat& cat) {};
	virtual void handlePresent(Mouse &theMouse)=0;

private:
};