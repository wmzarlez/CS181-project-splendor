#pragma once
#include "game.h"

class MinimaxAgent: public Agent{
public:
    MinimaxAgent(int index);

    static constexpr int totalDepth = 4;
    
    virtual Action getAction(const GameState& state);
    virtual std::string get_name();
    // int evaluatePlayerGameState(const GameState& state) const;
    inline int evaluatePlayerPoint(const GameState& state, int playerInd) const;
    std::vector<int> evaluateGamestate(const GameState& state) const;
    std::vector<int> getPtsRecursion(GameState state, int searchDepth) const;
    // int getActRecursion(GameState& state, int depth);
    // Action getOptimalAct(GameState& state);
    
private:
    int playerIndex;
};
