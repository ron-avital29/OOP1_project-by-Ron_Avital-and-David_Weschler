#pragma once

#include "KillCat.h"

KillCat::KillCat(sf::Texture* aTexture)
	: Present(aTexture)
{}

void KillCat::handlePresent(Mouse& theMouse)
{
    m_sound.setBuffer(Singleton::instance().getSoundBuffer(KILL_CAT));
    m_sound.play();

    theMouse.setKillCat(true);
}