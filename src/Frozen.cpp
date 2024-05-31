#pragma once

#include "Frozen.h"

Frozen::Frozen(sf::Texture* aTexture)
    : Present(aTexture)
{}

void Frozen::handlePresent(Mouse& theMouse)
{
	theMouse.setFreezeCats(true);
}