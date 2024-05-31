#pragma once

#include "Base.h"

class StaticObj : public Base
{
public:
	StaticObj(sf::Texture* aTexture);
	virtual void handleCollision(Base& unknownObj) = 0;

private:
};