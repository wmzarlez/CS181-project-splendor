#pragma once
#include "game.h"
#include "cstdint"

class HumanAgent: public Agent{
public:
    virtual Action getAction(const GameState& state) const;
    virtual std::uint16_t getGemAvailable(const GameState& state) const;
    HumanAgent(int index);
private:
    int playerIndex;
};

