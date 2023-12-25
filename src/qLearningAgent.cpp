#include "qLearningAgent.h"

extern Options options;

void QLearningAgent::load_weights(std::string address){

}

void QLearningAgent::store_weights(std::string address){

}

void QLearningAgent::update_weights(const GameState& state, Action action, const GameState& nextState){
    
}

std::unordered_map<std::string, float> QLearningAgent::get_features(const GameState& state){

    return std::unordered_map<std::string, float>();
}

float QLearningAgent::get_weight(std::string){

    return 0.0;
}

QLearningAgent::QLearningAgent(int index): playerIndex(index){

    
}

Action QLearningAgent::getAction(const GameState& state){
    std::cout<<"QLearningAgent getAction()"<<std::endl;

    return Action();
}