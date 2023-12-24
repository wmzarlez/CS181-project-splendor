#include "qLearningAgent.h"

extern Options options;

void QValueWeights::load_weights(std::string address){

}

void QValueWeights::store_weights(std::string address){

}

void QValueWeights::update_weights(const GameState& state, Action action, const GameState& nextState){
    
}

QLearningAgent::QLearningAgent(int index): playerIndex(index){}

Action QLearningAgent::getAction(const GameState& state){
    std::cout<<"QLearningAgent getAction()"<<std::endl;

    return Action();
}