#include "splendor.h"

extern Options options;

NoblePile::NoblePile(){
    Noble noble1={.nobleId=1, .point=3, .bonusRequired={0,0,0,4,4}};
    allNoble[0]=noble1;
    
    Noble noble2={.nobleId=2, .point=3, .bonusRequired={4,4,0,0,0}};
    allNoble[1]=noble2;

    Noble noble3={.nobleId=3, .point=3, .bonusRequired={3,0,0,3,3}};
    allNoble[2]=noble3;

    Noble noble4={.nobleId=4, .point=3, .bonusRequired={3,3,0,0,3}};
    allNoble[3]=noble4;

    Noble noble5={.nobleId=5, .point=3, .bonusRequired={4,0,0,0,4}};
    allNoble[4]=noble5;

    Noble noble6={.nobleId=6, .point=3, .bonusRequired={0,4,4,0,0}};
    allNoble[5]=noble6;

    Noble noble7={.nobleId=7, .point=3, .bonusRequired={3,3,3,0,0}};
    allNoble[6]=noble7;

    Noble noble8={.nobleId=8, .point=3, .bonusRequired={0,3,3,3,0}};
    allNoble[7]=noble8;

    Noble noble9={.nobleId=9, .point=3, .bonusRequired={0,0,4,4,0}};
    allNoble[8]=noble9;

    Noble noble10={.nobleId=10, .point=3, .bonusRequired={0,0,3,3,3}};
    allNoble[9]=noble10;
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
GameState::GameState(): cardPile(std::make_shared<CardPile>()),totalNobalPile(std::make_shared<NoblePile>()){
    for(int i=0;i<3;i++){                                                   //初始化market    col1   col2   col3
        for(int j=0;j<4;j++){                                               ////// level1 r1  00     01      02
            market[i][j]=get_card(*(cardPile.get()),i+1);                   ////// level2 r2  10     11      12
        }                                                                   ////// level3 r3  20     21      22
    }
    numPlayer=options.get_option<int>("-p");
    numTurn=0;
    if(numPlayer==2){                    //两个玩家
        numNoble=3;                      //贵族个数
         for(int i=0;i<6;i++){
            if(i==5){
                gemPile[i]=5;            //初始化宝石堆
            }
            else{
                gemPile[i]=4;
            }
        }

        std::vector<Noble> numble_vector=get_noble(*(totalNobalPile.get()),numNoble);         //初始化贵族
        for(int i=0;i<3;i++){
            noblePile[i]=numble_vector[i];
        }
        
    }
    else if(numPlayer==3){
        numNoble=4;                    //贵族数
        for(int i=0;i<6;i++){
            gemPile[i]=5;             //宝石堆
        }
        
        std::vector<Noble> numble_vector=get_noble(*(totalNobalPile.get()),numNoble);    //初始化贵族
        for(int i=0;i<4;i++){
            noblePile[i]=numble_vector[i];
        }
    }
    else if (numPlayer==4){ 
        numNoble=5;             //贵族数
        for(int i=0;i<6;i++){
            if(i==5){
                gemPile[i]=5;      //宝石堆
            }
            else{
                gemPile[i]=7;
            }
        }

        std::vector<Noble> numble_vector=get_noble(*(totalNobalPile.get()),numNoble);    //初始化贵族
        for(int i=0;i<5;i++){
            noblePile[i]=numble_vector[i];
        }
    }
    else{
        options.usage();   
        exit(0);
    }
}

GameState::GameState(const GameState &other):numTurn(other.numTurn), cardPile(other.cardPile), totalNobalPile(other.totalNobalPile),
    numNoble(other.numNoble), numPlayer(other.numPlayer), paintbrush(nullptr) {  
    for(int i=0;i<6;i++){
        gemPile[i]=other.gemPile[i];
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            market[i][j]=other.market[i][j];
        }
    }
    for(int i=0;i<5;i++){
        noblePile[i]=other.noblePile[i];
    }
    for(int i=0;i<numPlayer;i++){
        playerBoards[i]=other.playerBoards[i];
    }

}

std::vector<Action> GameState::get_legal_action(int playerIndex) const{
    
    return std::vector<Action>();
}

void GameState::apply_action(Action action, int playerindex){          //改变玩家playboard的还没实现
    // check_nobel and print_table should be used in this function
    if(action.type==0){                      //SELECTGEMS = 0
        if(action.params[2]==6){             //拿一种宝石两颗
            remove_gem(findGemType(action.params[0]));
            remove_gem(findGemType(action.params[1]));
            for(int i=3;i<6;i++){                             //drop 宝石，若type 为 blank 自动跳过
                add_gem(findGemType(action.params[i]));
            }
            playerBoards[playerindex].gemsOwnwd[action.params[0]]+=2;
        }
        else{                                //拿三种不同的宝石
            remove_gem(findGemType(action.params[0]));
            remove_gem(findGemType(action.params[1]));
            remove_gem(findGemType(action.params[2]));
            for(int i=3;i<6;i++){
                add_gem(findGemType(action.params[i]));
            }
            playerBoards[playerindex].gemsOwnwd[action.params[0]]++;
            playerBoards[playerindex].gemsOwnwd[action.params[1]]++;
            playerBoards[playerindex].gemsOwnwd[action.params[2]]++;
        }
        int playernum=options.get_option<int>("-p");
        for(int i=0;i<playernum;i++){
            check_noble(i);
        }
        print_table();
    }
    else if(action.type==1){                  //  BUYCARD = 1
        int cardscore=market[action.params[0]][action.params[1]].point;    
        int helpgem[6]={0};            //记录被买的卡多少钱
        int playerInitGem[6]={};      //记录玩家在购买该牌之前原有宝石情况
        int gemcost[6]={0};            //最终花费了什么种类的宝石分别多少个
        for (int i=0;i<6;i++){
            helpgem[i]=market[action.params[0]][action.params[1]].cost[i];               
        }
        for (int i=0;i<6;i++){
            playerInitGem[i]=playerBoards[playerindex].gemsOwnwd[i];     
        }
        for (int i=0;i<6;i++){                //先扣除玩家已有宝石，再把这些宝石放回宝石堆
            playerBoards[playerindex].gemsOwnwd[i]-=helpgem[i];          //假设全部花费普通宝石，之后再去扣除特殊宝石
        }
        for (int i=0;i<6;i++){                
           if(playerBoards[playerindex].gemsOwnwd[i]<0){
                playerBoards[playerindex].gemsOwnwd[5]+=playerBoards[playerindex].gemsOwnwd[i];    //不够就说明花万能宝石
                playerBoards[playerindex].gemsOwnwd[i]=0;     //扣除玩家宝石
           }
        }
        for (int i=0;i<6;i++){                
            gemcost[i]=playerInitGem[i]-playerBoards[playerindex].gemsOwnwd[i];  //玩家花费了哪些宝石
        }
        for (int i=0;i<6;i++){                
            if(gemcost[i]>0){           //表示购买花费了这种宝石
                for(int j=0;j<gemcost[i];j++){       //花费几个放回几次
                    add_gem(findGemType(i));      //回到宝石堆
                }
            }
        }

        playerBoards[playerindex].score+=cardscore;
        playerBoards[playerindex].bonuses[findGemType(market[action.params[0]][action.params[1]].bonusGem)]++;      //获得bonus
        add_card_random(action.params[0]+1,action.params[1]);     //替换掉被买的牌
        if(playerBoards[playerindex].gemsOwnwd[5]<0){     //扣除过多，报错
            std::cout<<"apply action 输入非法,买了买不起的牌"<<std::endl;
            options.usage();   
            exit(0);
        }
        int playernum=options.get_option<int>("-p");
        for(int i=0;i<playernum;i++){
            check_noble(i);
        }
        print_table();
    }
    else if(action.type==2){                  //  RESERVECARD = 2
        if(action.params[2]==1){
            playerBoards[playerindex].gemsOwnwd[5]++;
        }
        for(int i=0;i<3;i++){
            if(playerBoards[playerindex].reservedCards[i].cardId!=0){
                playerBoards[playerindex].reservedCards[i]=market[action.params[0]][action.params[1]];
                break;
            }
        }
        remove_card(action.params[0]+1,action.params[1]);
        int playernum=options.get_option<int>("-p");
        for(int i=0;i<playernum;i++){
            check_noble(i);
        }
        print_table();
    }
    else if(action.type==3){                  // SKIP = 3
        int playernum=options.get_option<int>("-p");
        for(int i=0;i<playernum;i++){
            check_noble(i);
        }
        print_table();
    }
    else{
        std::cout << "apply wrong action type or action illegal!!";
        options.usage();
        exit(0);
    }
}

bool GameState::is_win() {
    // check if someone wins
    int playnum = options.get_option<int>("-p");
    bool pan = false;
    const int WINNING_SCORE = 15;

    if (playnum >= 2 && playnum <= 4) {
        for (int i = 0; i < playnum; ++i) {
            if (playerBoards[i].score >= WINNING_SCORE) {
                pan = true;
                std::cout << "Player " << i + 1 << " wins" << std::endl;
            }
        }
        return pan;
    } else {
        std::cout << "Illegal number of players";
        options.usage();
        exit(0);
    }
}

void GameState::check_noble(int playerIndex){
    int playnum = options.get_option<int>("-p");
    if(playnum==2){
        for(int i=0;i<3;i++){
            bool satisfy=true;
            for(int j=0;j<5;j++){
                if(noblePile[i].bonusRequired[j]==playerBoards[playerIndex].bonuses[j]){
                    continue;
                }
                else{
                    satisfy=false;
                }
            }
            if(satisfy==true){
                playerBoards->score+=3;
                remove_noble(i);
            }
        }
    }
    else if(playnum==3){
        for(int i=0;i<4;i++){
            bool satisfy=true;
            for(int j=0;j<5;j++){
                if(noblePile[i].bonusRequired[j]==playerBoards[playerIndex].bonuses[j]){
                    continue;
                }
                else{
                    satisfy=false;
                }
            }
            if(satisfy==true){
                playerBoards[playerIndex-1].score+=3;
                remove_noble(i);
            }
        }
    }
    else if(playnum==4){
        for(int i=0;i<5;i++){
            bool satisfy=true;
            for(int j=0;j<5;j++){
                if(noblePile[i].bonusRequired[j]==playerBoards[playerIndex].bonuses[j]){
                    continue;
                }
                else{
                    satisfy=false;
                }
            }
            if(satisfy==true){
                playerBoards->score+=3;
                remove_noble(i);
                remove_noble(noblePile[i].nobleId);
            }
        }
    }
    else{
        std::cout<<"playernum error"<<std::endl;
        options.usage();   
        exit(0);
    }
}

void GameState::print_table() const{
    // use std::format

}

void GameState::add_card_random(int cardLevel, int cardColumnIndex){
    Card newcard=get_card(*(cardPile.get()),cardLevel);
    add_card_explicit(cardLevel,cardColumnIndex,newcard.cardId);
}
void GameState::add_card_explicit(int cardLevel, int cardColumnIndex, int cardId){
    if(cardId>0&&cardId<41){
        Card newcard=(*(cardPile.get())).level1Pile[cardId-1];
        market[cardLevel-1][cardColumnIndex]=newcard;
        (*(cardPile.get())).level1Pile[cardId-1]={};
    }
    else if(cardId>40&&cardId<71){
        Card newcard=(*(cardPile.get())).level2Pile[cardId-1-40];
        market[cardLevel-1][cardColumnIndex]=newcard;
        (*(cardPile.get())).level2Pile[cardId-1-40]={};
    }
    else if(cardId>70&&cardId<91){
        Card newcard=(*(cardPile.get())).level3Pile[cardId-1-40-30];
        market[cardLevel-1][cardColumnIndex]=newcard;
        (*(cardPile.get())).level3Pile[cardId-1-40-30]={};
    }
    else if(cardId==0){
        Card newcard={};
        market[cardLevel-1][cardColumnIndex]=newcard;
    }
    else{
        std::cout << "add Illegal explicit card";
        options.usage();
        exit(0);
    }
    std::cout << "add Illegal explicit card";
    options.usage();
    exit(0);
}
void GameState::remove_card(int cardLevel, int cardColumnIndex){
    market[cardLevel-1][cardColumnIndex]={};
}
void GameState::add_gem(Gem gemType){
    gemPile[gemType]+=1;
}
void GameState::remove_gem(Gem gemType){
    if(gemType!=6){
        gemPile[gemType]-=1;
    }
}
void GameState::remove_noble(int nobleIndex){
    noblePile[nobleIndex]={};
}
bool GameState::ableToBuy(int playerIndex,Card theCard){                //辅助函数，getaction时使用帮助判断
    int numyellow=playerBoards[playerIndex].gemsOwnwd[5];
    bool able=true;
    for (int i=0;i<5;i++){
        if(playerBoards[playerIndex].gemsOwnwd[i]+playerBoards[playerIndex].bonuses[i]>=theCard.cost[i]){
            continue;
        }
        else{
            int remain=theCard.cost[i]-playerBoards[playerIndex].gemsOwnwd[i]-playerBoards[playerIndex].bonuses[i];
            if(remain<=numyellow){
                numyellow-=remain;
                continue;
            }
            else{
                able=false;
                break;
            }
        }
    }
    return able;
}  
Card get_card(CardPile &cardPile,int level){                       //输入派对，随机抽卡
    //std::cout<<"hello";
    Card defaultCard = {.point = -2, .bonusGem=BLANK_, .cardLevel=0, .cardId=0, .cost = {10,10,10,10,10}};
    //std::cout<<defaultCard.point<<" ";
    srand((unsigned) time(NULL));
    if(level==1){
        if(cardPile.level1CardRemained==0){
            return defaultCard;
        }
        int count=0;
        int goal=rand()%(cardPile.level1CardRemained);
        for (int i=0;i<40;i++){
            if(cardPile.level1Pile[i].point!=-2){
                if(count==goal){
                    Card mid=cardPile.level1Pile[i];
                    //cardPile.level1Pile[i]=defaultCard;
                    cardPile.level1CardRemained--;
                    return mid;
                }
                else{
                    count++;
                }
            }
        }
    }
    else if(level==2){
        if(cardPile.level2CardRemained==0){
            return defaultCard;
        }
        int count=0;
        int goal=rand()%(cardPile.level2CardRemained);
        for (int i=0;i<30;i++){
            if(cardPile.level2Pile[i].point!=-2){
                if(count==goal){
                    Card mid=cardPile.level2Pile[i];
                    //cardPile.level2Pile[i]=defaultCard;
                    cardPile.level2CardRemained--;
                    return mid;
                }
                else{
                    count++;
                }
            }
        }
    }
    else if(level==3){
        if(cardPile.level3CardRemained==0){
            return defaultCard;
        }
        int count=0;
        int goal=rand()%(cardPile.level3CardRemained);
        for (int i=0;i<20;i++){
            if(cardPile.level3Pile[i].point!=-2){
                if(count==goal){
                    Card mid=cardPile.level3Pile[i];
                    //cardPile.level3Pile[i]=defaultCard;
                    cardPile.level3CardRemained--;
                    return mid;
                }
                else{
                    count++;
                }
            }
        }
    }
    else{
        std::cout<<"getcard input level illegal"<<std::endl;
        options.usage();   
        exit(0);
    }
}
std::vector<Noble> get_noble(NoblePile &noblepile, int num) {
    srand((unsigned)time(NULL));
    std::vector<Noble> ans;
    int countnum = 0;
    while (countnum < num) {
        int index = rand() % 10;
        if (noblepile.allNoble[index].point != 0) {
            ans.push_back(noblepile.allNoble[index]);
            noblepile.allNoble[index] = {};      // 重置被选中的noble
            countnum++;
        }
    }
    return ans;
}
Gem findGemType(int input){
    switch (input)
    {
    case 0:
        return WHITE;
    case 1:
        return BLUE;
    case 2:
        return GREEN;
    case 3:
        return RED;
    case 4:
        return BLACK;
    case 5:
        return YELLOW;
    case 6:
        return BLANK_;
    default:
        std::cout<<"findGemType input error";
        break;
    }
}