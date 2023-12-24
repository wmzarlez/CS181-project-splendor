#pragma once

class Visualization{
public:
    virtual void draw_card(int cardLevel, int cardIndex, int cardId) = 0;
    virtual void erase_card(int cardLevel, int cardIndex) = 0;
    virtual void draw_gem(int gemType) = 0;
    virtual void erase_gem(int gemType) = 0;
    virtual void draw_noble(int nobleIndex, int nobleId) = 0;
    virtual void erase_noble(int nobleIndex) = 0;
};