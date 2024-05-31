#pragma once

#include "Present.h"

class KillCat : public Present
{
public:
	KillCat(sf::Texture* aTexture);

	virtual void handlePresent(Mouse& theMouse);

private:
	sf::Sound m_sound;
};