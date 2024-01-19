#include "minimaxAgent.h"
#include <cstdint>
#include <chrono>
#include <limits>
extern Options options;

MinimaxAgent::MinimaxAgent(int index): playerIndex(index){}

int MinimaxAgent::evaluatePlayerPoint(const GameState& state) const{
    if(state.playerBoards[playerIndex].score == 15) return std::numeric_limits<int>::max();
    std::vector<float> otherPlayerPoint;
    int myPoint = std::numeric_limits<float>::min();
    for(std::uint16_t playerInd=0; playerInd<state.numPlayer; ++playerInd){
        int tmpPt = state.playerBoards[playerInd].score * 2;
        for(std::uint16_t i=0; i<5; ++i) tmpPt += state.playerBoards[playerInd].bonuses[i];
        for(std::uint16_t i=0; i<5; ++i) tmpPt += state.playerBoards[playerInd].gemsOwnwd[i]; 
        tmpPt += state.playerBoards[playerInd].gemsOwnwd[5] * 2;

        if(playerInd == playerIndex) { myPoint = tmpPt; }
        else otherPlayerPoint.emplace_back(tmpPt); 
    }
    int evaluatePoint = 0.f;
    
    for(std::uint16_t i=0; i<otherPlayerPoint.size(); ++i){
        if(myPoint > otherPlayerPoint[i]) evaluatePoint += pow(otherPlayerPoint[i] - myPoint, 2);
        else evaluatePoint += -pow(otherPlayerPoint[i] - myPoint, 2);
    } 
    return evaluatePoint;
}

Action MinimaxAgent::getAction(const GameState& state){
    printf("Minimax agent getAction... ");
    std::pair<Action, int> optActPair = std::make_pair(Action(), std::numeric_limits<int>::min());
    std::vector<Action> possibleActs = state.get_legal_action(playerIndex);
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    for(std::uint16_t i=0; i<possibleActs.size(); ++i){
        GameState newStat = state;
        newStat.apply_action(possibleActs[i], playerIndex);
        int tmpPt = getActRecursion(newStat, 1);
        if(optActPair.second < tmpPt) optActPair = std::make_pair(possibleActs[i], tmpPt); 
    }
    std::cout << " It takes " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count() << " millisecs.\n" << std::endl;
    return optActPair.first;

}

int MinimaxAgent::getActRecursion(GameState state, int depth){

    if(depth == totalDepth) return evaluatePlayerPoint(state);

    std::vector<Action> possiAct = state.get_legal_action((playerIndex + depth) % state.numPlayer);
    int bestPt;
    if(depth % state.numPlayer == 0){
        bestPt = std::numeric_limits<int>::min();   
        for(std::uint16_t i=0; i<possiAct.size(); ++i){
            GameState newState = state;
            newState.apply_action(possiAct[i], (playerIndex + depth) % state.numPlayer);
            int tmpPt = getActRecursion(newState, depth+1);
            if(tmpPt > bestPt) bestPt = tmpPt;
        }
    }
    else{
        bestPt = std::numeric_limits<int>::max();   
        for(std::uint16_t i=0; i<possiAct.size(); ++i){
            GameState newState = state;
            newState.apply_action(possiAct[i], (playerIndex + depth) % state.numPlayer);
            int tmpPt = getActRecursion(newState, depth+1);
            if(tmpPt < bestPt) bestPt = tmpPt;
        }
    }
    return bestPt;
}
