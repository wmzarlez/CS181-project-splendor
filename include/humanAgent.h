#pragma once
#include "game.h"

class HumanAgent: public Agent{
public:
    Action getAction(GameState state);
};

