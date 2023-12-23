#pragma once
#include <vector>
#include <iostream>

typedef enum{
    WHITE = 0,
    BLUE = 1,
    GREEN = 2,
    RED = 3,
    BLACK = 4,
    YELLOW = 5,
    BLANK = 6
} Gem;

typedef enum{
    SELECTGEMS = 0,
    BUYCARD = 1,
    RESERVECARD = 2,
    SKIP = 3
} ActionType;

struct Card{
    int point = 0;
    Gem bonusGem;
    int cost[5];
};

struct Noble{
    int point = 3;
    int bonusRequired[5];
};

struct Action{
    ActionType type = SELECTGEMS;
    int params[6];
};

class PlayerBoard{
public:
    // PlayerBoard init
    PlayerBoard();
private:
    int bonuses[5];
    int gemsOwnwd[6];
    Card reservedCards[3];
};

class GameState{
public:
    // GameState init
    GameState();
    std::vector<Action> get_legal_action(int playerIndex);
    bool apply_action(Action action);
    // return true if one player wins
    bool is_win();
    // Check whether a player can get a noble.
    // If true, increase the player's point, and remove that noble
    void check_noble(int playerIndex);

    //  when you need to add/remove tokens, use functions below
    void add_card_random(int cardLevel, int cardIndex);
    void add_card_explicit(int cardLevel, int cardIndex, int cardId);
    void remove_card(int cardLevel, int cardIndex);
    void add_gem(Gem gemType);
    void remove_gem(Gem gemType);
    void add_noble_random(int nobleIndex);
    void add_noble_explicit(int nobleIndex, int nobleId);
    void remove_noble(int nobleIndex);

private:
    int gemPile[6] = {4,4,4,4,4,5};

    Card market[3][4];
    Card level1Pile[40];
    Card level2Pile[30];
    Card level3Pile[20];

    Noble noblePile[5];
    int numNoble = 3;

    PlayerBoard playerBoards[4];
    int numPlayer = 2;
};