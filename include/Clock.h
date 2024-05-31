#pragma once

#include "Present.h"

const float ADD_TIME = 20.f;

class Clock : public Present
{
public:
	Clock(sf::Texture* aTexture);

	virtual void handlePresent(Mouse& theMouse);

private:	
};