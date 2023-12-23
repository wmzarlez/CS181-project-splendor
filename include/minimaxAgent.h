#pragma once
#include "game.h"


class MinimaxAgent: public Agent{
public:
    Action getAction(GameState state);
};