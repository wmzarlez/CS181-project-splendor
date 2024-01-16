#pragma once
#include "game.h"



class GreedyAgent: public Agent{
public:
    virtual Action getAction(const GameState& state);
    virtual float evaluatePoint(const GameState& state) const;
    virtual Action getLegalAction(const GameState& state) const;

    GreedyAgent(int index);
private:
    int playerIndex;
    static constexpr int recursionDepth = 8;
};