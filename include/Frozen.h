#pragma once

#include "Present.h"

class Frozen : public Present
{
public:
    Frozen(sf::Texture* aTexture);

    virtual void handlePresent(Mouse& theMouse);

private:
};