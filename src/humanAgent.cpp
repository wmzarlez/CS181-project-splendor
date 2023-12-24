#include "humanAgent.h"

extern Options options;

HumanAgent::HumanAgent(int index): playerIndex(index){}

Action HumanAgent::getAction(const GameState& state){
    // if action not in state.get_legal_action(), ask again.
    std::cout<<"HumanAgent getAction()"<<std::endl;

    return Action();
}