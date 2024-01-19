#include "randomAgent.h"
#include "splendor.h"

RandomAgent::RandomAgent(int playerIndex):playerIndex(playerIndex){}

Action RandomAgent::getAction(const GameState& state){
    auto actionVector=state.get_legal_action(playerIndex);
    int actionIndex=rand()%(actionVector.size());
    return actionVector[actionIndex];
}
