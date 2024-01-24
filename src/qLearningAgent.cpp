#include <fstream>
#include <sstream>
#include <algorithm>
#include "qLearningAgent.h"
#include <omp.h>

extern Options options;

void QLearningAgent::load_weights(){
    std::ifstream version("../qTrainingLog/version.txt");
    std::string line;
    if(!version.is_open()){
        std::cout<<"Error: Read version fail."<<std::endl;
        std::cout<<"Using the default weight."<<std::endl;
        weights["bias"]=1.56102;
        weights["cards-to-closest-noble"]=-4.22793;
        weights["reserved-cards-point"]=0.22722;
        weights["2-max-card-values-to-me"]=0.695397;
        weights["cards-owned"]=5.99116;
        weights["4-max-card-values-to-opponents"]=-0.440487;
        weights["gem-owned"]=3.525472;
        weights["gold-gem"]=-0.588584;
        weights["my-points"]=6.54455;
        weights["points-opponents-get-after-2-turns"]=-0.678302;
        weights["6-max-card-values-to-me"]=0.450985;
        weights["4-max-card-values-to-me"]=0.984092;
        weights["turns"]=-1.95876;
        return;
    }
    std::getline(version,line);
    int bestModel=atoi(line.c_str());
    std::getline(version,line);
    latestModel=atoi(line.c_str());

    std::ifstream weightData("../qTrainingLog/"+std::string(std::to_string(bestModel))+".txt");
    if(!weightData.is_open()){
        std::cout<<"Error: Read weights fail."<<std::endl;
        exit(1);
    }

    float weight;
    while(std::getline(weightData,line)){
        char charName[64]={0};
        sscanf(line.c_str(),"%s\t%f",charName,&weight);
        weights[std::string(charName)]=weight;
    }
}

void QLearningAgent::store_weights(){
    std::ifstream version("../qTrainingLog/version.txt");
    if(!version.is_open())return;

    std::ofstream weightData("../qTrainingLog/"+std::string(std::to_string(latestModel+1))+".txt");
    //latestModel++;
    for(auto iter=weights.begin();iter!=weights.end();iter++){
        weightData<<iter->first<<'\t'<<iter->second<<std::endl;
    }
}

void QLearningAgent::update_weights(GameState nowState, Action action){
    float reward=get_reward(nowState);
    float nowQValue=Q_Value(nowState,action);
    float lastQValue=Q_Value(lastState,lastAction);
    
    float diff=reward+gamma*nowQValue-lastQValue;

    lastState.apply_action(lastAction,playerIndex);
    for(auto iter=weights.begin();iter!=weights.end();iter++){
        iter->second+=alpha*diff*get_feature(lastState,iter->first);
    }
}

float QLearningAgent::market_card_value(const GameState& state, const Card& card, int pIndex){
    float cardValue=2.0;
    int gemCost=0;
    for(int i=0;i<5;i++){
        gemCost+=card.cost[i];
    }
    cardValue-=gemCost/5.0;
    cardValue+=card.point;
    
    std::vector<float> penalty;
    for(int i=0;i<5;i++){
        int gemOwned=state.playerBoards[pIndex].gemsOwnwd[i]+state.playerBoards[pIndex].bonuses[i];
        int gemNeeded=card.cost[i]-gemOwned;
        for(int i=0;i<gemNeeded;i++){
            penalty.push_back(penaltyTable[i]);
        }
    }

    std::sort(penalty.begin(), penalty.end(), std::greater<float>());
    for(int i=0;i<penalty.size();i++){
        if(i<state.playerBoards[pIndex].gemsOwnwd[(int)YELLOW]){
            continue;
        }
        cardValue-=penalty[i];
    }

    return cardValue;
}

float QLearningAgent::get_feature(const GameState& state, std::string featureName){
    if(featureName=="bias"){
        return 1.0;
    }
    else if(featureName=="cards-to-closest-noble"){
        float minFeature=9.0/2.0;
        for(int i=0;i<5;i++){
            if(state.noblePile[i].nobleId==0)continue;
            int feature=0;
            for(int j=0;j<5;j++){
                int bonusesNeeded=state.noblePile[i].bonusRequired[j]-state.playerBoards[playerIndex].bonuses[j];
                if(bonusesNeeded>0){
                    feature+=bonusesNeeded;
                }
            }
            if((float)(feature/2.0)<minFeature){
                minFeature=(float)(feature/2.0);
            }
        }
        return minFeature;
    }
    else if(featureName=="cards-owned"){
        float feature=0;
        for(int i=0;i<5;i++){
            feature+=state.playerBoards[playerIndex].bonuses[i];
        }
        return feature/10.0;
    }
    else if(featureName=="gem-owned"){
        float feature=0;
        for(int i=0;i<6;i++){
            feature+=state.playerBoards[playerIndex].gemsOwnwd[i];
        }
        return feature/10.0;
    }
    else if(featureName=="gold-gem"){
        return state.playerBoards[playerIndex].gemsOwnwd[(int)YELLOW]/10.0;
    }
    else if(featureName=="my-points"){
        return state.playerBoards[playerIndex].score/2.0;
    }
    else if(featureName=="points-opponents-get-after-2-turns"){
        int maxPoint=0;
        for(int i=0;i<state.numPlayer;i++){
            if(i==playerIndex)continue;

            int opponentScoreNow=state.playerBoards[i].score;
            //#pragma omp parallel for
            for(auto a1:state.get_legal_action(i)){
                GameState s1=state;
                s1.apply_action(a1,i);
                for(auto a2:s1.get_legal_action(i)){
                    GameState s2=s1;
                    s2.apply_action(a2,i);
                    int opponentScoreAfter2Turns=s2.playerBoards[i].score;
                    if(opponentScoreAfter2Turns-opponentScoreNow>maxPoint){maxPoint=opponentScoreAfter2Turns-opponentScoreNow;}
                }
            }
        }
        
        return (float)maxPoint;
    }
    else if(featureName=="6-max-card-values-to-me"){
        float feature=0;
        std::vector<float> cardValueVector;
        for(int i=0;i<3;i++){
            for(int j=0;j<4;j++){
                Card card=state.market[i][j];
                if(card.cardId==0)continue;
                cardValueVector.push_back(market_card_value(state,card,playerIndex));
            }
        }
        for(int i=0;i<3;i++){
            Card card=state.playerBoards[playerIndex].reservedCards[i];
            if(card.cardId==0)continue;
            cardValueVector.push_back(1.1*market_card_value(state,card,playerIndex));
        }
        std::sort(cardValueVector.begin(),cardValueVector.end(),std::greater<float>());
        for(int i=0;i<6;i++){
            feature+=cardValueVector[i];
        }
        return feature/4.0;
    }
    else if(featureName=="4-max-card-values-to-me"){
        float feature=0;
        std::vector<float> cardValueVector;
        for(int i=0;i<3;i++){
            for(int j=0;j<4;j++){
                Card card=state.market[i][j];
                if(card.cardId==0)continue;
                cardValueVector.push_back(market_card_value(state,card,playerIndex));
            }
        }
        for(int i=0;i<3;i++){
            Card card=state.playerBoards[playerIndex].reservedCards[i];
            if(card.cardId==0)continue;
            cardValueVector.push_back(1.1*market_card_value(state,card,playerIndex));
        }
        std::sort(cardValueVector.begin(),cardValueVector.end(),std::greater<float>());
        for(int i=0;i<4;i++){
            feature+=cardValueVector[i];
        }
        return feature/4.0;
    }
    else if(featureName=="2-max-card-values-to-me"){
        float feature=0;
        std::vector<float> cardValueVector;
        for(int i=0;i<3;i++){
            for(int j=0;j<4;j++){
                Card card=state.market[i][j];
                if(card.cardId==0)continue;
                cardValueVector.push_back(market_card_value(state,card,playerIndex));
            }
        }
        for(int i=0;i<3;i++){
            Card card=state.playerBoards[playerIndex].reservedCards[i];
            if(card.cardId==0)continue;
            cardValueVector.push_back(1.1*market_card_value(state,card,playerIndex));
        }
        std::sort(cardValueVector.begin(),cardValueVector.end(),std::greater<float>());
        for(int i=0;i<2;i++){
            feature+=cardValueVector[i];
        }
        return feature/4.0;
    }
    else if(featureName=="4-max-card-values-to-opponents"){
        float feature=0;
        std::vector<float> cardValueVector;
        for(int pIndex=0;pIndex<state.numPlayer;pIndex++){
            for(int i=0;i<3;i++){
                for(int j=0;j<4;j++){
                    Card card=state.market[i][j];
                    if(card.cardId==0)continue;
                    cardValueVector.push_back(market_card_value(state,card,pIndex));
                }
            }
            // for(int i=0;i<3;i++){
            //     Card card=state.playerBoards[pIndex].reservedCards[i];
            //     if(card.cardId==0)continue;
            //     cardValueVector.push_back(0.5*market_card_value(state,card,pIndex));
            // }
        }
        
        std::sort(cardValueVector.begin(),cardValueVector.end(),std::greater<float>());
        for(int i=0;i<4;i++){
            feature+=cardValueVector[i];
        }
        return feature/4.0;
    }
    else if(featureName=="turns"){
        return state.numTurn/10.0;
    }
    else if(featureName=="reserved-cards-point"){
        float reservedPoint=0;
        for(int i=0;i<3;i++){
            if(state.playerBoards[playerIndex].reservedCards[i].cardId!=0){
                reservedPoint+=state.playerBoards[playerIndex].reservedCards[i].point;
            }
        }
        return reservedPoint/4;
    }
    else{
        std::cout<<"No such feature."<<std::endl;
        return 0;
    }
}

float QLearningAgent::Q_Value(GameState state, Action action){
    state.apply_action(action,playerIndex);
    return State_Value(state);
}

float QLearningAgent::State_Value(const GameState& state){
    float value=0;
    for(auto iter=weights.begin();iter!=weights.end();iter++){
        value+=(iter->second)*(get_feature(state,iter->first));
    }
    return value;
}

float QLearningAgent::get_reward(const GameState& state){
    float reward=-1;

    if(state.playerBoards[playerIndex].score>=15)reward+=5;
    
    reward+=(state.playerBoards[playerIndex].score-lastState.playerBoards[playerIndex].score);

    // int numCard=0;
    // for(int i=0;i<5;i++){
    //     numCard+=state.playerBoards[playerIndex].bonuses[i];
    // }
    for(int i=0;i<5;i++){
        if(state.playerBoards[playerIndex].bonuses[i]>lastState.playerBoards[playerIndex].bonuses[i]){
            reward+=1.5;
        }
    }
    for(int i=0;i<5;i++){
        if(state.playerBoards[playerIndex].gemsOwnwd[i]>lastState.playerBoards[playerIndex].gemsOwnwd[i]){
            reward+=0.2;
        }
    }

    for(int i=0;i<3;i++){
        if(state.playerBoards[playerIndex].reservedCards[i].cardLevel==3 &&
            lastState.playerBoards[playerIndex].reservedCards[i].cardLevel!=3){
            reward+=0.5;
        }
    }

    for(int i=0;i<state.numPlayer;i++){
        if(i==playerIndex)continue;
        reward-=(state.playerBoards[i].score-lastState.playerBoards[i].score)*0.2;
    }

    return reward;
}

QLearningAgent::QLearningAgent(int index, float alpha, float gamma):
    playerIndex(index), alpha(alpha), gamma(gamma){
    load_weights();
    noTraining=options.get_option<bool>("-no-training");
}

Action QLearningAgent::getAction(const GameState& state){
    std::cout<<"Approximate Q-Learning agent choosing action..."<<std::endl;
    Action bestAction;
    bestAction.type=SKIP;
    float maxQValue=-65535;
    auto actionVector=state.get_legal_action(playerIndex);

    for(auto iter=actionVector.begin();iter!=actionVector.end();iter++){
        if(iter->type==SKIP)continue;
        float qValue=Q_Value(state,*iter);
        if(qValue>maxQValue){
            maxQValue=qValue;
            bestAction=*iter;
        }
    }

    if(!noTraining){
        int prob=rand()%100;
        epsilon=0;
        if(prob<epsilon){
            int numAction=actionVector.size();
            prob=rand()%(numAction);
            bestAction=actionVector[prob];
        }
    }

    // update weight
    if(state.numTurn<=1){
        lastState=state;
        lastAction=bestAction;
    }
    else{
        update_weights(state,bestAction);
        if(!noTraining)store_weights();
        lastState=state;
        lastAction=bestAction;
    }
    return bestAction;
}
