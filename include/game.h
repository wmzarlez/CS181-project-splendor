#pragma once
#include "splendor.h"

class Agent{
public:
    virtual Action getAction(GameState state) = 0;
};

class Game{
public:
    Game();
    void run();
    // train for approximate Q-Learning
    void train();

private:
    GameState state;
    std::vector<Agent*> players;
    int numPlayer;
};