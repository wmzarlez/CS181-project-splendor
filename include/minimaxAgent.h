#pragma once
#include "game.h"

class MinimaxAgent: public Agent{
public:
    virtual Action getAction(const GameState& state);
    virtual std::string get_name(){return "Adversarial Search Agent";}
    int evaluatePlayerPoint(const GameState& state) const;
    int getActRecursion(GameState state, int depth);
    MinimaxAgent(int index);
    static constexpr int totalDepth = 4;
private:
    int playerIndex;
};
