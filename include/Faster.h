#pragma once

#include "Present.h"

const float INCREASED = 300.f;

class Faster : public Present
{
public:
    Faster(sf::Texture* aTexture);

    virtual void handlePresent(Mouse& theMouse);

private:
};