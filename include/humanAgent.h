#pragma once
#include "game.h"
#include "cstdint"

class HumanAgent: public Agent{
public:
    virtual Action getAction(const GameState& state);
    virtual std::uint16_t getGemAvailable(const GameState& state) const;
    virtual bool isLegalAction(const GameState& state, const Action myAction) const;
    HumanAgent(int index);
private:
    int playerIndex;
};

