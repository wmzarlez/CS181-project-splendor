#pragma once

#include "splendor.h"

class Agent{
public:
    virtual Action getAction(const GameState& state) = 0;
};

class Game{
public:
    Game();
    void run();
    // train for approximate Q-Learning
    void train();

private:
    GameState state;
    std::vector<std::unique_ptr<Agent>> players;
    int numPlayer;
};