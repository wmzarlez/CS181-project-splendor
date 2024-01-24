#include "minimaxAgent.h"
#include <cstdint>
#include <chrono>
#include <limits>
#include <array>
#include <omp.h>
extern Options options;

constexpr int MY_INT_MAX = std::numeric_limits<int>::max();
constexpr int MY_INT_MIN  = std::numeric_limits<int>::min();
#define SKIP_ACT ActionType::SKIP

MinimaxAgent::MinimaxAgent(int index): playerIndex(index){}
std::string MinimaxAgent::get_name() { return "Adversarial Search Agent"; }

inline int MinimaxAgent::evaluatePlayerPoint(const GameState& state, int playerInd) const{
    int tmpPt = state.playerBoards[playerInd].score * 100;
    for(std::uint16_t i=0; i<5; ++i) tmpPt += state.playerBoards[playerInd].bonuses[i];
    for(std::uint16_t i=0; i<5; ++i) tmpPt += state.playerBoards[playerInd].gemsOwnwd[i]; 
    tmpPt += state.playerBoards[playerInd].gemsOwnwd[5] * 2;
    return tmpPt;
}
std::vector<int> MinimaxAgent::evaluateGamestate(const GameState& state) const{
    std::vector<int> playerPt;
    for(std::uint16_t playerInd=0; playerInd < state.numPlayer; ++playerInd){
        playerPt.emplace_back(evaluatePlayerPoint(state, playerInd));
    }
    return playerPt;
}
// Value function given a specific state.
// int MinimaxAgent::evaluatePlayerGameState(const GameState& state) const{
//     if(state.playerBoards[playerIndex].score >= 15) return MY_INT_MAX;
//     std::vector<int> otherPlayerPoint;
//     int myPoint = MY_INT_MIN;
//     for(std::uint16_t playerInd=0; playerInd<state.numPlayer; ++playerInd){
//         int tmpPt = evaluatePlayerPoint(state, playerInd);
//         if(playerInd == playerIndex) { myPoint = tmpPt; }
//         else                         { otherPlayerPoint.emplace_back(tmpPt); }
//     }   
//     int evaluatePoint = 0;
    
//     // for(std::uint16_t playerInd=0; playerInd<otherPlayerPoint.size(); ++playerInd){
//     //     if(myPoint > otherPlayerPoint[playerInd]){ evaluatePoint += pow(otherPlayerPoint[playerInd] - myPoint, 2); }
//     //     else                                     { evaluatePoint -= pow(otherPlayerPoint[playerInd] - myPoint, 2); }
//     // }
//     evaluatePoint /= 20;
//     evaluatePoint += evaluatePlayerPoint(state, playerIndex);
//     return evaluatePoint;
// }

Action MinimaxAgent::getAction(const GameState& state){
    printf("Minimax agent getAction... ");
    std::pair<Action, int> optActPair = std::make_pair(Action(), MY_INT_MIN);
    std::vector<Action> possibleActs = state.get_legal_action(playerIndex);
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    int actNum = possibleActs.size();
    #pragma omp parallel for
    for(std::uint16_t i=0; i<actNum; ++i){
        if(possibleActs[i].type != SKIP_ACT){
            GameState newStat = state;
            newStat.apply_action(possibleActs[i], playerIndex);
            // int tmpPt = getActRecursion(newStat, 1);
            std::vector<int> tmpPts = getPtsRecursion(newStat, 1);
            int myPoint = 0;
            for(std::uint16_t j=0; j<tmpPts.size(); ++j){
                if(playerIndex != j) 
                    myPoint += (tmpPts[playerIndex] - tmpPts[j]);
            }
            myPoint /= 5;
            myPoint += tmpPts[playerIndex];
            #pragma omp critical
            {
                if(optActPair.second < myPoint){ 
                    optActPair = std::make_pair(possibleActs[i], myPoint); 
                }
            }
        }
         
    }
    
    std::cout << "It takes " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count() << " millisecs.\n" << std::endl;
    if(optActPair.second == MY_INT_MIN) optActPair.first.type = SKIP_ACT;
    return optActPair.first;

}
std::vector<int> MinimaxAgent::getPtsRecursion(GameState state, int searchDepth) const{
    if(searchDepth == totalDepth){ // End of search.
        return evaluateGamestate(state);
    }

    int thisPlayerIndex = (playerIndex + searchDepth) % state.numPlayer;
    std::vector<Action> possiActs = state.get_legal_action(thisPlayerIndex);
    int bestPt = MY_INT_MIN;
    std::vector<int> optimalStatePts;

    // This agent should choose its prefered maximizing state.
    for(std::uint16_t actInd=0; actInd<possiActs.size(); ++actInd){
        if(possiActs[actInd].type == SKIP_ACT)
            if(possiActs.size() > 1) continue;
        GameState newState = state;
        newState.apply_action(possiActs[actInd], thisPlayerIndex);

        // If the estimated point of this agent is optimal, the agent shall choose this board.
        std::vector<int> tmpPts = getPtsRecursion(newState, searchDepth+1);
        
        int estimatePt = 0;
        for(std::uint16_t i=0; i<tmpPts.size(); ++i){
            if(thisPlayerIndex != i) 
                estimatePt += (tmpPts[thisPlayerIndex] - tmpPts[i]);
        }
        estimatePt /= 5;
        estimatePt += tmpPts[thisPlayerIndex];
        if(bestPt < estimatePt){
            bestPt = estimatePt;
            optimalStatePts.clear();
            optimalStatePts = tmpPts;
        }
    }

    return optimalStatePts;



}

// int MinimaxAgent::getActRecursion(GameState& state, int depth){
//     if(depth == totalDepth) return evaluatePlayerGameState(state);

//     std::vector<Action> possiAct = state.get_legal_action((playerIndex + depth) % state.numPlayer);
//     int bestPt;

//     if(depth % state.numPlayer == 0){ // Maximizing agent.
//         bestPt = MY_INT_MIN;   
//         for(std::uint16_t i=0; i<possiAct.size(); ++i){

//             if(possiAct[i].type == SKIP_ACT)
//                 if(possiAct.size() > 1) continue; // Pass ActionType::SKIP if there are some available actions.
//                 // else printf("No available action except for ActionType::SKIP.\n");

//             GameState newState = state;
//             newState.apply_action(possiAct[i], (playerIndex + depth) % state.numPlayer);
//             int tmpPt = getActRecursion(newState, depth+1);
//             if(tmpPt > bestPt) bestPt = tmpPt;
//         }
//     }
//     else{ // Minimizing Agent.
//         bestPt = MY_INT_MAX;   
//         for(std::uint16_t i=0; i<possiAct.size(); ++i){

//             if(possiAct[i].type == SKIP_ACT)
//                 if(possiAct.size() > 1) continue; // Pass ActionType::SKIP if there are some available actions.
//                 // else printf("No available action except for ActionType::SKIP.\n");

//             GameState newState = state; 
//             newState.apply_action(possiAct[i], (playerIndex + depth) % state.numPlayer);
//             int tmpPt = getActRecursion(newState, depth+1);
//             if(tmpPt < bestPt) bestPt = tmpPt;
//         }
//     }
//     return bestPt;
// }
