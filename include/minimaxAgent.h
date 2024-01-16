#pragma once
#include "game.h"

class MinimaxAgent: public Agent{
public:
    virtual Action getAction(const GameState& state);
    virtual float evaluatePlayerPoint(const GameState& state) const;
    virtual Action getLegalAction_SELECTGEMS(const GameState& state) const;
    virtual Action getLegalAction_BUYCARD(const GameState& state) const;
    virtual Action getLegalAction_RESERVECARD(const GameState& state) const;
    MinimaxAgent(int index);
private:
    int playerIndex;
};
