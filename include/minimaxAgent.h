#pragma once
#include "game.h"

class MinimaxAgent: public Agent{
public:
    MinimaxAgent(int index);

    static constexpr int totalDepth = 4;
    
    virtual Action getAction(const GameState& state);
    virtual std::string get_name();
    int evaluatePlayerPoint(const GameState& state) const;
    int getActRecursion(GameState state, int depth);
    
    // Action getOptAct(const GameState& state);
    
private:
    int playerIndex;
};
