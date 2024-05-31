#pragma once

#include "Clock.h"

Clock::Clock(sf::Texture* aTexture)
	: Present(aTexture)
{}

void Clock::handlePresent(Mouse& mouse)
{
	mouse.setCountDown(ADD_TIME, true);
}