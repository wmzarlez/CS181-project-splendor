#pragma once
#include "game.h"

class GreedyAgent: public Agent{
public:
    virtual Action getAction(const GameState& state);
    GreedyAgent(int index);
private:
    int playerIndex;
};