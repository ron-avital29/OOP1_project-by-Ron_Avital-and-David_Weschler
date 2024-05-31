#pragma once

#include "Present.h"

class Heart : public Present
{
public:
	Heart(sf::Texture* aTexture);

	virtual void handlePresent(Mouse& theMouse);

private:	
};