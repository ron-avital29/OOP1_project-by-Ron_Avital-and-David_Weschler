#pragma once

#include "Present.h"

class Bomb : public Present
{
public:
    Bomb(sf::Texture* aTexture);

    virtual void handlePresent(Mouse& theMouse);

private:
};