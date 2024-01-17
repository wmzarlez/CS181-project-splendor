#include "greedyAgent.h"


#include <tuple>
#include <optional>
#include <numeric>
#include <array>
#include <cstdint>
#include <chrono>

extern Options options;

GreedyAgent::GreedyAgent(int index): playerIndex(index){}

float GreedyAgent::evalPt(const GameState& state) const{
    float evaluatePoints = state.playerBoards[playerIndex].score / 2.;
    for(short i=0; i<5; evaluatePoints += state.playerBoards[playerIndex].gemsOwnwd[i++] / 10.);
    evaluatePoints += state.playerBoards[playerIndex].gemsOwnwd[5] * .3;
    for(short i=0; i<5; evaluatePoints += state.playerBoards[playerIndex].bonuses[i++] / 10.);
    return evaluatePoints;
}



float GreedyAgent::getActRecursion(GameState state, int depth){
    if(depth > recursionDepth) return evalPt(state);
    std::vector<Action> possibleActs = state.get_legal_action(playerIndex);
    float bestPoint = std::numeric_limits<float>::min();

    for(std::uint16_t i=0; i<possibleActs.size(); ++i){
        GameState newStat = state;
        newStat.apply_action(possibleActs[i], playerIndex);
        float tmpPt = getActRecursion(newStat, depth+1);
        if(tmpPt > bestPoint) bestPoint = tmpPt;
    }
    return bestPoint;
}

// Initial depth 0, num(searchDepth) = num(actions taken). If searchDepth = 5, then take 5 sequential actions and return at depth 5. 
Action GreedyAgent::getAction(const GameState& state){
    std::cout << "Greedy agent choosing action...";
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

    std::pair<Action, float> optActPair = std::make_pair(Action(), std::numeric_limits<float>::min());
    
    std::vector<Action> possibleActs = state.get_legal_action(playerIndex);
    for(std::uint16_t i=0; i<possibleActs.size(); ++i){
        GameState newStat = state;
        newStat.apply_action(possibleActs[i], playerIndex);
        float tmpPt = getActRecursion(state, 1);
        if(optActPair.second < tmpPt) { optActPair = std::make_pair(possibleActs[i], tmpPt); }
    }
    printf(" It takes %f seconds.\n", std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startTime).count());
    return optActPair.first;
}


