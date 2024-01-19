#pragma once
#include "game.h"

class RandomAgent: public Agent{
public:
    virtual Action getAction(const GameState& state);
    RandomAgent(int playerIndex);
private:
    int playerIndex;
};