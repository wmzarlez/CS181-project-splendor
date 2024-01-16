#include "minimaxAgent.h"

extern Options options;

MinimaxAgent::MinimaxAgent(int index): playerIndex(index){}


float MinimaxAgent::evaluatePlayerPoint(const GameState& state) const{
    std::vector<float> otherPlayerPoint;
    float myPoint = std::numeric_limits<float>::min();
    for(short playerInd=0; playerInd<state.numPlayer; ++playerInd){
        float point = state.playerBoards[playerInd].score / 2;
        for(short i=0; i<5; ++i) point += state.playerBoards[playerInd].bonuses[i] / 10.;
        for(short i=0; i<5; ++i) point += state.playerBoards[playerInd].gemsOwnwd[i] / 10.; 
        point += state.playerBoards[playerInd].gemsOwnwd[5] * 0.3;

        if(playerInd == playerIndex) { myPoint = point; }
        else otherPlayerPoint.emplace_back(point); 
    }
    float evaluatePoint = 0.f;
    for(short i=0; i<otherPlayerPoint.size(); ++i) evaluatePoint += pow(otherPlayerPoint[i] - myPoint, 2);
    return evaluatePoint;
}

Action MinimaxAgent::getLegalAction_SELECTGEMS(const GameState& state) const{
    // Need to prune unnecessary actions, like you have 10 gems and select 3 gems and dump 3 gems.
    // 12 cards and their respective points and required gems already known. For each card, if gem required is [1,1,1,1,2],
    // for example, then each gem is valued as (point of card * gem number of this kind) / (1+1+1+1+2).
    // If no specific cards you want to buy while you can't? card count = 8/9/10, don't make this action.
    // That can be helpful in reducing branching factors.
    // If so? How to value these action(or specific cards)?
    // The gap between you and ANY card you can't afford might be [3, -1, -1, 2, -2], golden gems already used up.
    // Each gem is at cost 1/3 turn at each turn SELECTGEMS. 1/2 turn if you choose 2 same ones.

    // Then if you can make up the gap with (8/9/10 -> 10), e.t.c., use 1/2/3 to trade 2/3 gems, 

}

Action MinimaxAgent::getLegalAction_BUYCARD(const GameState& state) const{
    // Rule of thumb: use up regular gems first, then use golden gem. 
}

Action MinimaxAgent::getLegalAction_RESERVECARD(const GameState& state) const{
    
}

Action MinimaxAgent::getAction(const GameState& state){
    std::vector<Action> legalActions = state.get_legal_action(playerIndex);
    if(!legalActions.size()) return Action();
    // for()
    
    return Action();
}