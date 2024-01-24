#include "greedyAgent.h"
#include <tuple>
#include <optional>
#include <numeric>
#include <array>
#include <cstdint>
#include <chrono>
#include <omp.h>

extern Options options;

GreedyAgent::GreedyAgent(int index): playerIndex(index){}

int GreedyAgent::evalPt(const GameState& state) const{
    //if(state.playerBoards[playerIndex].score >= 15) return std::numeric_limits<int>::max();
    int evaluatePoints = state.playerBoards[playerIndex].score * 1000;
    for(short i=0; i<5; evaluatePoints += 50 * state.playerBoards[playerIndex].gemsOwnwd[i++]);
    evaluatePoints += state.playerBoards[playerIndex].gemsOwnwd[5] * 60;
    for(short i=0; i<5; evaluatePoints += state.playerBoards[playerIndex].bonuses[i++] * 420);
    if(state.playerBoards[playerIndex].reservedCards[0].cardId!=0){
        evaluatePoints+=state.playerBoards[playerIndex].reservedCards[0].point;
    }

    return evaluatePoints;
}

int GreedyAgent::getActRecursion(GameState state, int depth){
    if(depth > recursionDepth) return evalPt(state);
    std::vector<Action> possibleActs = state.get_legal_action(playerIndex);
    int bestPoint = std::numeric_limits<int>::min();

    for(std::uint16_t i=0; i<possibleActs.size(); ++i){
        GameState newStat = state;
        newStat.apply_action(possibleActs[i], playerIndex);
        int tmpPt = getActRecursion(newStat, depth+1);
        if(tmpPt > bestPoint) bestPoint = tmpPt;
    }
    return bestPoint;
}

// Initial depth 0, num(searchDepth) = num(actions taken). If searchDepth = 5, then take 5 sequential actions and return at depth 5. 
Action GreedyAgent::getAction(const GameState& state){
    std::cout << "Greedy agent choosing action..."<<std::endl;
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    std::pair<Action, int> optActPair = std::make_pair(Action(), std::numeric_limits<int>::min());
    
    std::vector<Action> possibleActs = state.get_legal_action(playerIndex);
    int size=possibleActs.size();
    #pragma omp parallel for
    for(std::uint16_t i=0; i<size; ++i){ 
        GameState newStat = state;
        newStat.apply_action(possibleActs[i], playerIndex);
        int tmpPt = getActRecursion(newStat, 1);
        #pragma omp critical
        if(optActPair.second < tmpPt){optActPair = std::make_pair(possibleActs[i], tmpPt);}
    }
    //std::cout << "Num of legal actions is "<<size<<std::endl;
    std::cout << " It takes " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count() << " millisecs." << std::endl;
    return optActPair.first;
}


