#include "greedyAgent.h"


#include <tuple>
#include <optional>
#include <numeric>
#include <array>

extern Options options;

GreedyAgent::GreedyAgent(int index): playerIndex(index){}

// inline int fetchCardPoint(int cardLevel, int cardIndex){
//     return 0; 
// }
// inline int fetchCardCost(int cardLevel, int cardIndex){
//     return 0;
// }

// inline double evaluateAction(const GameState& state, const Action& action){
//     if(action.type == ActionType::BUYCARD){
//         // int cardLevel = action.params[0] + 1;
//         int cardPoint = fetchCardPoint(action.params[0] + 1, action.params[1]);
//         int cardCost = fetchCardCost(action.params[0] + 1, action.params[1]);

//         return cardPoint;
//     }
//     else if(action.type == ActionType::SELECTGEMS){

//     }
//     else if(action.type == ActionType::RESERVECARD){
        
//     }
//     else{
//         return 0;
//     }

// Action GreedyAgent::getAction(const GameState& state){
//     std::cout<<"greedyAgent getAction()"<<std::endl;
//     std::size_t depth = 5;
//     std::vector<Action> legalActions = state.get_legal_action(playerIndex);
//     // Action* bestAction;
//     if(!legalActions.size()) return Action(); // Seems that this case won't happen. ActionType::SKIP.

//     // I suppose store 3 most optimal ACtion for each type.
//     std::optional<std::tuple<Action, int>> buyCard = std::nullopt;
//     std::optional<std::tuple<Action, int>> buyGem = std::nullopt;
//     std::optional<Action> reserveCard = std::nullopt;

//     for(std::size_t i=0; i<legalActions.size(); ++i){
//         if(legalActions[i].type == ActionType::BUYCARD){
//             int cardPoint = fetchCardPoint(legalActions[i].params[0] + 1, legalActions[i].params[1]);
//             int cardCost = fetchCardCost(legalActions[i].params[0] + 1, legalActions[i].params[1]);
//             if(!buyCard.has_value() || std::get<1>(buyCard.value()) < cardPoint){
//                 buyCard = std::make_tuple(legalActions[i], cardPoint);
//             }
//         }
//         else if(legalActions[i].type == ActionType::SELECTGEMS){
//             int gemGainedNum = 0;
//             for(short j=0; j<3; ++j) if(legalActions[i].params[j] != Gem::BLANK_) ++gemGainedNum;
//             for(short j=3; j<6; ++j) if(legalActions[i].params[j] != Gem::BLANK_) --gemGainedNum;
//             if(!buyGem.has_value() || std::get<1>(buyGem.value()) < gemGainedNum){
//                     buyCard = std::make_tuple(legalActions[i], gemGainedNum);
//             }
//         }
//         else if(legalActions[i].type == ActionType::RESERVECARD){
//             if(!reserveCard.has_value()) reserveCard = legalActions[i];
//         }

//     }
//     if(buyCard.has_value()) return std::get<0>(buyCard.value());
//     if(buyGem.has_value()) return std::get<0>(buyGem.value());
//     if(reserveCard.has_value()) return reserveCard.value();
//     return Action();
// }

float GreedyAgent::evaluatePoint(const GameState& state) const{
    float evaluatePoints = state.playerBoards[playerIndex].score / 2.;
    for(short i=0; i<5; evaluatePoints += state.playerBoards[playerIndex].gemsOwnwd[i++] / 10.);
    evaluatePoints += state.playerBoards[playerIndex].gemsOwnwd[5] * .3;
    for(short i=0; i<5; evaluatePoints += state.playerBoards[playerIndex].bonuses[i++] / 10.);
    return evaluatePoints;
}


Action GreedyAgent::getLegalAction(const GameState& state) const{
    
}
// float getActionHelper(GameState state, int depth, int playerIndex){
//     if(depth > searchDepth) return evaluatePoint(state);
//     std::vector<Action> legalActions = state.get_legal_action(playerIndex);
//     float bestPoint = std::numeric_limits<float>::min();

//     if(!legalActions.size()){
//         std::cout << "No legal action available at some points in depth " << depth << ". It is not supposed to be happening since agent is expecting state.get_legal_action() to always return an actionType::SKIP.\n";
//         return evaluatePoint(state);
//     }

//     for(int i=0; i<legalActions.size(); ++i){
//         GameState newState = state;
//         newState.apply_action(legalActions[i], playerIndex);
//         float tmpPoint = getActionHelper(newState, depth+1, playerIndex);
//         if(bestPoint < tmpPoint) bestPoint = tmpPoint; 
//     }
//     return bestPoint;
// }

// Initial depth 0, num(searchDepth) = num(actions taken). If searchDepth = 5, then take 5 sequential actions and return at depth 5. 
Action GreedyAgent::getAction(const GameState& state){
    Action bestAction = Action();
    // float bestPoint = std::numeric_limits<float>::min();
    // std::vector<Action> legalActions = state.get_legal_action(playerIndex);
    //  if(!legalActions.size()){
    //     std::cout << "No legal action available. It is not supposed to be happening since agent is expecting state.get_legal_action() to always return an actionType::SKIP.\n";
    //     return Action();
    // }
    // for(int i=0; i<legalActions.size(); ++i){
    //     GameState newState = state;
    //     newState.apply_action(legalActions[i], playerIndex);
    //     // float tmpPoint = getActionHelper(newState, 1, playerIndex);
    //     if(bestPoint < tmpPoint){
    //         bestPoint = tmpPoint;
    //         bestAction = legalActions[i];
    //     }
    // }
    return bestAction;
}


