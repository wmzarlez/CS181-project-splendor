#pragma once
#include "game.h"

class QLearningAgent: public Agent{
public:
    QLearningAgent(int index, float alpha=0.00, float gamma=0.9);
    virtual Action getAction(const GameState& state);
private:
    void load_weights();
    void store_weights();
    void update_weights(GameState nowState, Action action);

    float market_card_value(const GameState& state, const Card& card, int pIndex);
    float get_feature(const GameState& state, std::string featureName);
    float Q_Value(GameState state, Action action);
    float State_Value(const GameState& state);
    float get_reward(const GameState& state);

    bool noTraining;
    int latestModel=0;
    int playerIndex;
    std::unordered_map<std::string, float> weights;
    float alpha;
    float gamma;
    float epsilon;
    float penaltyTable[7]={1.0/5.0, 1.0/4.0, 1.0/3.0, 2.0/5.0, 0.5, 0.5, 0.5};
    GameState lastState;
    Action lastAction;
    
};

