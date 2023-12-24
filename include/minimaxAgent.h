#pragma once
#include "game.h"

class MinimaxAgent: public Agent{
public:
    virtual Action getAction(const GameState& state);
    MinimaxAgent(int index);
private:
    int playerIndex;
};
