#include "greedyAgent.h"

extern Options options;

GreedyAgent::GreedyAgent(int index): playerIndex(index){}

Action GreedyAgent::getAction(const GameState& state){
    std::cout<<"greedyAgent getAction()"<<std::endl;

    return Action();
}