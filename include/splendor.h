#pragma once
#include <memory>
#include <vector>
#include "util.hpp"
#include "../opengl/include/visualization.hpp"

typedef enum{
    WHITE = 0,
    BLUE = 1,
    GREEN = 2,
    RED = 3,
    BLACK = 4,
    YELLOW = 5,
    BLANK_ = 6
} Gem;

typedef enum{
    SELECTGEMS = 0,
    BUYCARD = 1,
    RESERVECARD = 2,
    SKIP = 3
} ActionType;

struct Card{
    int point = -2;
    Gem bonusGem = BLANK_;
    int cardLevel = 0; // cardLevel is start from 1
    int cardId = 0; // cardId is start from 1
    int cost[5] = {10,10,10,10,10};
};

//Card card = {.point = -2, .bonusGem, .cost = {10,10,10,10,10}}

struct Noble{
    int nobleid=0;   //nobleid start from 1
    int point = 0;
    int bonusRequired[5] = {10,10,10,10,10};
};

/*
 * params are used to describe an action, details are below
 * SELECTGEMS:
 * the first 3 params are the gems player selected
 * the last 3 params are the gems player droped (usually BLANK(6))
 * BUYCARD:
 * (params[0],params[1]) represents (cardLevel-1,cardIndex)
 * they can be just used as market[params[0]][params[1]]
 * params remained are useless
 * RESERVECARD:
 * the first 2 params are similar with BUYCARD
 * the third param is an indicator of whether a gold/YELLOW gem can be got
 * 0 -- no YELLOW gem, 1 -- get a YELLOW gem
 * params remained are useless
 * SKIP:
 * all params are useless
*/

struct Action{
    ActionType type = SKIP;
    int params[6];
};

class PlayerBoard{
public:
    // PlayerBoard init
    //PlayerBoard();
//private:
    int bonuses[5]={};
    int gemsOwnwd[6]={};
    Card reservedCards[3]={};
    int score=0;
};

struct CardPile{
    Card level1Pile[40];
    int level1CardRemained = 40;
    Card level2Pile[30];
    int level2CardRemained = 30;
    Card level3Pile[20];
    int level3CardRemained = 20;
    CardPile();
};

struct NoblePile{           //存放所有贵族牌信息，初始化游戏时随机从中抽取需要个数的贵族
    Noble allNoble[10];
    NoblePile();
};

class GameState{
public:
    // GameState init
    GameState();
    std::vector<Action> get_legal_action(int playerIndex) const;
    void apply_action(Action action);
    // return true if one player wins
    bool is_win();
    // Check whether a player can get a noble.
    // If true, increase the player's point, and remove that noble
    void check_noble(int playerIndex);
    void print_table() const;

    //  when you need to add/remove tokens, use functions below
    void add_card_random(int cardLevel, int cardColumnIndex);
    void add_card_explicit(int cardLevel, int cardColumnIndex, int cardId);   
    void remove_card(int cardLevel, int cardColumnIndex);
    void add_gem(Gem gemType);
    void remove_gem(Gem gemType);
    void add_noble_random(int nobleIndex);
    void add_noble_explicit(int nobleIndex, int nobleId);
    void remove_noble(int nobleIndex);
    int numTurn = 0;

    int gemPile[6] = {4,4,4,4,4,5};

    Card market[3][4];
    std::shared_ptr<CardPile> cardPile;

    std::shared_ptr<NoblePile> totalNobalPile;          
    //储存了所有的贵族卡信息，唯一的作用就是初始化noblepile
    Noble noblePile[5];
    int numNoble = 3;

    PlayerBoard playerBoards[4];
    int numPlayer ;

    Visualization* paintbrush;
};
Card get_card(CardPile &cardPile,int level);
std::vector<Noble> get_noble(NoblePile &noblepile, int num);