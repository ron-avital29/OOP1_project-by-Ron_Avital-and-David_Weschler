#pragma once

#include "Bomb.h"

Bomb::Bomb(sf::Texture* aTexture)
    : Present(aTexture)
{}

void Bomb::handlePresent(Mouse& theMouse)
{
    theMouse.doBomb();
    theMouse.setGotBombed(true);
}