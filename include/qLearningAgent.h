#pragma once
#include "game.h"

class QLearningAgent: public Agent{
public:
    Action getAction(GameState state);
};

