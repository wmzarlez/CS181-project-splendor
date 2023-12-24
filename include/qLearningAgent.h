#pragma once
#include "game.h"

class QValueWeights{
public:
    void load_weights(std::string address);
    void store_weights(std::string address);
    void update_weights(const GameState& state, Action action, const GameState& nextState);
    

};

class QLearningAgent: public Agent{
public:
    QLearningAgent(int index);
    virtual Action getAction(const GameState& state);
private:
    int playerIndex;
};

