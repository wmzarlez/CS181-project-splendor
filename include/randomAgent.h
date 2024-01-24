#pragma once
#include "game.h"

class RandomAgent: public Agent{
public:
    virtual Action getAction(const GameState& state);
    virtual std::string get_name(){return "Random Agent";}
    RandomAgent(int playerIndex);
private:
    int playerIndex;
};