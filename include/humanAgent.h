#pragma once
#include "game.h"

class HumanAgent: public Agent{
public:
    virtual Action getAction(const GameState& state);
    HumanAgent(int index);
private:
    int playerIndex;
};

