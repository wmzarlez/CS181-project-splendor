#include "splendor.h"

extern Options options;

PlayerBoard::PlayerBoard(){
    
}
CardPile::CardPile(){
    level1CardRemained=40;
    level2CardRemained=30;
    level3CardRemained=20;
    /*level 1*/
    Card card1 = {.point = 0, .bonusGem=RED, .cardLevel=1, .cardId=1, .cost = {3,0,0,0,0}};
    level1Pile[0] = card1;

    Card card2 = {.point = 0, .bonusGem=RED, .cardLevel=1, .cardId=2, .cost = {2,1,1,0,1}};
    level1Pile[1] = card2;

    Card card3 = {.point = 0, .bonusGem=WHITE, .cardLevel=1, .cardId=3, .cost = {0,0,0,2,1}};
    level1Pile[2] = card3;

    Card card4 = {.point = 0, .bonusGem=WHITE, .cardLevel=1, .cardId=4, .cost = {0,1,1,1,1}};
    level1Pile[3] = card4;

    Card card5 = {.point = 0, .bonusGem=WHITE, .cardLevel=1, .cardId=5, .cost = {3,1,0,0,1}};
    level1Pile[4] = card5;

    Card card6 = {.point = 0, .bonusGem=GREEN, .cardLevel=1, .cardId=6, .cost = {1,1,0,1,2}};
    level1Pile[5] = card6;

    Card card7 = {.point = 0, .bonusGem=GREEN, .cardLevel=1, .cardId=7, .cost = {2,1,0,0,0}};
    level1Pile[6] = card7;

    Card card8 = {.point = 0, .bonusGem=BLUE, .cardLevel=1, .cardId=8, .cost = {1,0,0,0,2}};
    level1Pile[7] = card8;

    Card card9 = {.point = 0, .bonusGem=BLACK, .cardLevel=1, .cardId=9, .cost = {0,0,3,0,0}};
    level1Pile[8] = card9;

    Card card10 = {.point = 0, .bonusGem=BLACK, .cardLevel=1, .cardId=10, .cost = {1,2,1,1,0}};
    level1Pile[9] = card10;

    Card card11 = {.point = 0, .bonusGem=WHITE, .cardLevel=1, .cardId=11, .cost = {0,1,2,1,1}};
    level1Pile[10] = card11;

    Card card12 = {.point = 0, .bonusGem=WHITE, .cardLevel=1, .cardId=12, .cost = {0,2,0,0,2}};
    level1Pile[11] = card12;

    Card card13 = {.point = 1, .bonusGem=BLUE, .cardLevel=1, .cardId=13, .cost = {0,0,0,4,0}};
    level1Pile[12] = card13;

    Card card14 = {.point = 0, .bonusGem=BLUE, .cardLevel=1, .cardId=14, .cost = {0,0,2,0,2}};
    level1Pile[13] = card14;

    Card card15 = {.point = 0, .bonusGem=BLUE, .cardLevel=1, .cardId=15, .cost = {1,0,1,1,1}};
    level1Pile[14] = card15;

    Card card16 = {.point = 0, .bonusGem=BLACK, .cardLevel=1, .cardId=16, .cost = {2,2,0,1,0}};
    level1Pile[15] = card16;

    Card card17 = {.point = 1, .bonusGem=BLACK, .cardLevel=1, .cardId=17, .cost = {0,4,0,0,0}};
    level1Pile[16] = card17;

    Card card18 = {.point = 0, .bonusGem=BLACK, .cardLevel=1, .cardId=18, .cost = {0,0,2,1,0}};
    level1Pile[17] = card18;

    Card card19 = {.point = 1, .bonusGem=RED, .cardLevel=1, .cardId=19, .cost = {4,0,0,0,0}};
    level1Pile[18] = card19;

    Card card20 = {.point = 0, .bonusGem=GREEN, .cardLevel=1, .cardId=20, .cost = {0,1,0,2,2}};
    level1Pile[19] = card20;

    Card card21 = {.point = 0, .bonusGem=GREEN, .cardLevel=1, .cardId=21, .cost = {1,3,1,0,0}};
    level1Pile[20] = card21;

    Card card22 = {.point = 0, .bonusGem=GREEN, .cardLevel=1, .cardId=22, .cost = {0,0,3,0,0}};
    level1Pile[21] = card22;

    Card card23 = {.point = 1, .bonusGem=WHITE, .cardLevel=1, .cardId=23, .cost = {0,0,4,0,0}};
    level1Pile[22] = card23;

    Card card24 = {.point = 0, .bonusGem=RED, .cardLevel=1, .cardId=24, .cost = {1,1,1,0,1}};
    level1Pile[23] = card24;

    Card card25 = {.point = 0, .bonusGem=BLUE, .cardLevel=1, .cardId=25, .cost = {1,0,1,2,1}};
    level1Pile[24] = card25;

    Card card26 = {.point = 0, .bonusGem=BLUE, .cardLevel=1, .cardId=26, .cost = {0,1,3,1,0}};
    level1Pile[25] = card26;

    Card card27 = {.point = 0, .bonusGem=GREEN, .cardLevel=1, .cardId=27, .cost = {1,1,0,1,1}};
    level1Pile[26] = card27;

    Card card28 = {.point = 0, .bonusGem=GREEN, .cardLevel=1, .cardId=28, .cost = {0,2,0,2,0}};
    level1Pile[27] = card28;
    
    Card card29 = {.point = 1, .bonusGem=GREEN, .cardLevel=1, .cardId=29, .cost = {0,0,0,0,4}};
    level1Pile[28] = card29;

    Card card30 = {.point = 0, .bonusGem=BLUE, .cardLevel=1, .cardId=30, .cost = {1,0,2,2,0}};
    level1Pile[29] = card30;

    Card card31 = {.point = 0, .bonusGem=BLUE, .cardLevel=1, .cardId=31, .cost = {0,0,0,0,3}};
    level1Pile[30] = card31;

    Card card32 = {.point = 0, .bonusGem=WHITE, .cardLevel=1, .cardId=32, .cost = {0,3,0,0,0}};
    level1Pile[31] = card32;

    Card card33 = {.point = 0, .bonusGem=WHITE, .cardLevel=1, .cardId=33, .cost = {0,2,2,0,1}};
    level1Pile[32] = card33;

    Card card34 = {.point = 0, .bonusGem=RED, .cardLevel=1, .cardId=34, .cost = {1,0,0,1,3}};
    level1Pile[33] = card34;

    Card card35 = {.point = 0, .bonusGem=RED, .cardLevel=1, .cardId=35, .cost = {0,2,1,0,0}};
    level1Pile[34] = card35;

    Card card36 = {.point = 0, .bonusGem=RED, .cardLevel=1, .cardId=36, .cost = {2,0,1,0,2}};
    level1Pile[35] = card36;

    Card card37 = {.point = 0, .bonusGem=BLACK, .cardLevel=1, .cardId=37, .cost = {2,0,2,0,0}};
    level1Pile[36] = card37;

    Card card38 = {.point = 0, .bonusGem=BLACK, .cardLevel=1, .cardId=38, .cost = {1,1,1,1,0}};
    level1Pile[37] = card38;

    Card card39 = {.point = 0, .bonusGem=BLACK, .cardLevel=1, .cardId=39, .cost = {0,0,1,3,1}};
    level1Pile[38] = card39;

    Card card40 = {.point = 0, .bonusGem=RED, .cardLevel=1, .cardId=40, .cost = {2,0,0,2,0}};
    level1Pile[39] = card40;
    /*xxxxxxx*/
    /*level 2*/
    /*xxxxxxx*/
    Card card41 = {.point = 2, .bonusGem=RED, .cardLevel=2, .cardId=41, .cost = {3,0,0,0,5}}; 
    level2Pile[0] = card41;

    Card card42 = {.point = 3, .bonusGem=BLUE, .cardLevel=2, .cardId=42, .cost = {0,6,0,0,0}}; 
    level2Pile[1] = card42;

    Card card43 = {.point = 3, .bonusGem=GREEN, .cardLevel=2, .cardId=43, .cost = {0,0,6,0,0}}; 
    level2Pile[2] = card43;

    Card card44 = {.point = 3, .bonusGem=WHITE, .cardLevel=2, .cardId=44, .cost = {6,0,0,0,0}}; 
    level2Pile[3] = card44;

    Card card45 = {.point = 1, .bonusGem=BLACK, .cardLevel=2, .cardId=45, .cost = {3,0,3,0,2}}; 
    level2Pile[4] = card45;

    Card card46 = {.point = 2, .bonusGem=GREEN, .cardLevel=2, .cardId=46, .cost = {0,0,5,0,0}}; 
    level2Pile[5] = card46;

    Card card47 = {.point = 2, .bonusGem=BLACK, .cardLevel=2, .cardId=47, .cost = {0,0,5,3,0}}; 
    level2Pile[6] = card47;

    Card card48 = {.point = 1, .bonusGem=RED, .cardLevel=2, .cardId=48, .cost = {2,0,0,2,3}}; 
    level2Pile[7] = card48;

    Card card49 = {.point = 2, .bonusGem=BLACK, .cardLevel=2, .cardId=49, .cost = {0,1,4,2,0}}; 
    level2Pile[8] = card49;

    Card card50 = {.point = 1, .bonusGem=GREEN, .cardLevel=2, .cardId=50, .cost = {3,0,2,3,0}}; 
    level2Pile[9] = card50;

    Card card51 = {.point = 2, .bonusGem=WHITE, .cardLevel=2, .cardId=51, .cost = {0,0,0,5,0}}; 
    level2Pile[10] = card51;

    Card card52 = {.point = 3, .bonusGem=RED, .cardLevel=2, .cardId=52, .cost = {0,0,0,6,0}}; 
    level2Pile[11] = card52;

    Card card53 = {.point = 2, .bonusGem=WHITE, .cardLevel=2, .cardId=53, .cost = {0,0,1,4,2}}; 
    level2Pile[12] = card53;

    Card card54 = {.point = 2, .bonusGem=RED, .cardLevel=2, .cardId=54, .cost = {0,0,0,0,5}}; 
    level2Pile[13] = card54;

    Card card55 = {.point = 1, .bonusGem=WHITE, .cardLevel=2, .cardId=55, .cost = {0,0,3,2,2}}; 
    level2Pile[14] = card55;

    Card card56 = {.point = 2, .bonusGem=GREEN, .cardLevel=2, .cardId=56, .cost = {4,2,0,0,1}}; 
    level2Pile[15] = card56;

    Card card57 = {.point = 2, .bonusGem=BLUE, .cardLevel=2, .cardId=57, .cost = {5,3,0,0,0}}; 
    level2Pile[16] = card57;

    Card card58 = {.point = 3, .bonusGem=BLACK, .cardLevel=2, .cardId=58, .cost = {0,0,0,0,6}}; 
    level2Pile[17] = card58;

    Card card59 = {.point = 2, .bonusGem=GREEN, .cardLevel=2, .cardId=59, .cost = {0,5,3,0,0}}; 
    level2Pile[18] = card59;

    Card card60 = {.point = 1, .bonusGem=BLUE, .cardLevel=2, .cardId=60, .cost = {0,2,3,0,3}}; 
    level2Pile[19] = card60;

    Card card61 = {.point = 2, .bonusGem=BLACK, .cardLevel=2, .cardId=61, .cost = {5,0,0,0,0}}; 
    level2Pile[20] = card61;

    Card card62 = {.point = 2, .bonusGem=BLUE, .cardLevel=2, .cardId=62, .cost = {2,0,0,1,4}}; 
    level2Pile[21] = card62;

    Card card63 = {.point = 1, .bonusGem=BLUE, .cardLevel=2, .cardId=63, .cost = {0,2,2,3,0}}; 
    level2Pile[22] = card63;

    Card card64 = {.point = 2, .bonusGem=WHITE, .cardLevel=2, .cardId=64, .cost = {0,0,0,5,3}}; 
    level2Pile[23] = card64;

    Card card65 = {.point = 1, .bonusGem=WHITE, .cardLevel=2, .cardId=65, .cost = {2,3,0,3,0}}; 
    level2Pile[24] = card65;

    Card card66 = {.point = 2, .bonusGem=RED, .cardLevel=2, .cardId=66, .cost = {1,4,2,0,0}}; 
    level2Pile[25] = card66;

    Card card67 = {.point = 1, .bonusGem=BLACK, .cardLevel=2, .cardId=67, .cost = {3,2,2,0,0}};
    level2Pile[26] = card67;

    Card card68 = {.point = 1, .bonusGem=RED, .cardLevel=2, .cardId=68, .cost = {0,3,0,2,3}}; 
    level2Pile[27] = card68;

    Card card69 = {.point = 2, .bonusGem=BLUE, .cardLevel=2, .cardId=69, .cost = {0,5,0,0,0}}; 
    level2Pile[28] = card69;

    Card card70 = {.point = 1, .bonusGem=GREEN, .cardLevel=2, .cardId=70, .cost = {2,3,0,0,2}}; 
    level2Pile[29] = card70;
    /*xxxxxxx*/
    /*level 3*/
    /*xxxxxxx*/
    Card card71 = {.point = 4, .bonusGem=BLACK, .cardLevel=3, .cardId=71, .cost = {0,0,0,7,0}};
    level3Pile[0] = card71;

    Card card72 = {.point = 5, .bonusGem=RED, .cardLevel=3, .cardId=72, .cost = {0,0,7,3,0}};
    level3Pile[1] = card72;

    Card card73 = {.point = 4, .bonusGem=GREEN, .cardLevel=3, .cardId=73, .cost = {0,7,0,0,0}};
    level3Pile[2] = card73;

    Card card74 = {.point = 4, .bonusGem=WHITE, .cardLevel=3, .cardId=74, .cost = {3,0,0,3,6}};
    level3Pile[3] = card74;

    Card card75 = {.point = 3, .bonusGem=BLACK, .cardLevel=3, .cardId=75, .cost = {3,3,5,3,0}};
    level3Pile[4] = card75;

    Card card76 = {.point = 4, .bonusGem=BLACK, .cardLevel=3, .cardId=76, .cost = {0,0,3,6,3}};
    level3Pile[5] = card76;

    Card card77 = {.point = 4, .bonusGem=WHITE, .cardLevel=3, .cardId=77, .cost = {0,0,0,0,7}};
    level3Pile[6] = card77;

    Card card78 = {.point = 4, .bonusGem=GREEN, .cardLevel=3, .cardId=78, .cost = {3,6,3,0,0}};
    level3Pile[7] = card78;

    Card card79 = {.point = 5, .bonusGem=BLUE, .cardLevel=3, .cardId=79, .cost = {7,3,0,0,0}};
    level3Pile[8] = card79;

    Card card80 = {.point = 4, .bonusGem=RED, .cardLevel=3, .cardId=80, .cost = {0,3,6,3,0}};
    level3Pile[9] = card80;

    Card card81 = {.point = 4, .bonusGem=RED, .cardLevel=3, .cardId=81, .cost = {0,0,7,0,0}};
    level3Pile[10] = card81;

    Card card82 = {.point = 5, .bonusGem=BLACK, .cardLevel=3, .cardId=82, .cost = {0,0,0,7,3}};
    level3Pile[11] = card82;

    Card card83 = {.point = 5, .bonusGem=GREEN, .cardLevel=3, .cardId=83, .cost = {0,7,3,0,0}};
    level3Pile[12] = card83;

    Card card84 = {.point = 3, .bonusGem=GREEN, .cardLevel=3, .cardId=84, .cost = {5,3,0,3,3}};
    level3Pile[13] = card84;

    Card card85 = {.point = 4, .bonusGem=BLUE, .cardLevel=3, .cardId=85, .cost = {6,3,0,0,3}};
    level3Pile[14] = card85;

    Card card86 = {.point = 5, .bonusGem=WHITE, .cardLevel=3, .cardId=86, .cost = {3,0,0,0,7}};
    level3Pile[15] = card86;

    Card card87 = {.point = 4, .bonusGem=BLUE, .cardLevel=3, .cardId=87, .cost = {7,0,0,0,0}};
    level3Pile[16] = card87;

    Card card88 = {.point = 3, .bonusGem=RED, .cardLevel=3, .cardId=88, .cost = {3,5,3,0,3}};
    level3Pile[17] = card88;

    Card card89 = {.point = 3, .bonusGem=WHITE, .cardLevel=3, .cardId=89, .cost = {0,3,3,5,3}};
    level3Pile[18] = card89;

    Card card90 = {.point = 3, .bonusGem=BLUE, .cardLevel=3, .cardId=90, .cost = {3,0,3,3,5}};
    level3Pile[19] = card90;
}
GameState::GameState(): cardPile(std::make_shared<CardPile>()){
    numPlayer=options.get_option<int>("-p");
    numTurn=0;
    if(numPlayer==2){
        numNoble=3;
    }
    else if(numPlayer==3){
        numNoble=4;
        for(int i=0;i<6;i++){
            gemPile[i]=5;
        }
    }
    else if (numPlayer==4){
        numNoble=5;
        for(int i=0;i<6;i++){
            if(i==5){
                gemPile[i]=5;
            }
            else{
                gemPile[i]=7;
            }
        }
    }
    else{
        options.usage();   
        exit(0);
    }
}

std::vector<Action> GameState::get_legal_action(int playerIndex) const{
    
    return std::vector<Action>();
}

void GameState::apply_action(Action action){
    // check_nobel and print_table should be used in this function
    
}

bool GameState::is_win(){
    // check if some one wins
    
    return false;
}

void GameState::check_noble(int playerIndex){

}

void GameState::print_table() const{
    // use std::format

}

void GameState::add_card_random(int cardLevel, int cardColumnIndex){

}
void GameState::add_card_explicit(int cardLevel, int cardColumnIndex, int cardId){

}
void GameState::remove_card(int cardLevel, int cardColumnIndex){

}
void GameState::add_gem(Gem gemType){

}
void GameState::remove_gem(Gem gemType){

}
void GameState::add_noble_random(int nobleIndex){

}
void GameState::add_noble_explicit(int nobleIndex, int nobleId){

}
void GameState::remove_noble(int nobleIndex){

}