#pragma once

#include "Faster.h"

Faster::Faster(sf::Texture* aTexture)
    : Present(aTexture)
{}

void Faster::handlePresent(Mouse& theMouse)
{
    theMouse.setSpeed(INCREASED);
    theMouse.setFaster(true);
}