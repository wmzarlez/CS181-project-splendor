#pragma once
#include "game.h"

class QLearningAgent: public Agent{
public:
    QLearningAgent(int index);
    virtual Action getAction(const GameState& state);
private:
    void load_weights(std::string address);
    void store_weights(std::string address);
    void update_weights(const GameState& state, Action action, const GameState& nextState);
    std::unordered_map<std::string, float> get_features(const GameState& state);
    float get_weight(std::string);

    int playerIndex;
    std::unordered_map<std::string, float> weights;

};

