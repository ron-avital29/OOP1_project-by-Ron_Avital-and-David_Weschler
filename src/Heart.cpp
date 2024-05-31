#pragma once

#include "Heart.h"

Heart::Heart(sf::Texture* aTexture)
	: Present(aTexture)
{}

void Heart::handlePresent(Mouse& theMouse)
{
	theMouse.setLife(1, true);
}