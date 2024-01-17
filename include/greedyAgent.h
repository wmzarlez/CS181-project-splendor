#pragma once
#include "game.h"



class GreedyAgent: public Agent{
public:
    virtual Action getAction(const GameState& state);
    float evalPt(const GameState& state) const;
    float getActRecursion(GameState state, int depth);

    GreedyAgent(int index);
private:
    int playerIndex;
    static constexpr int recursionDepth = 8;
};