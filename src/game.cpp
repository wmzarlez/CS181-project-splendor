#include "game.h"
#include "humanAgent.h"
#include "minimaxAgent.h"
#include "qLearningAgent.h"
#include "greedyAgent.h"
extern Options options;

Game::Game(){
    // init every menber value
    // ********************************************
    // e.g.
    // // player 1
    // std::unique_ptr<Agent> player_ptr = std::make_unique<HumanAgent>();
    // players.emplace_back(std::move(player_ptr));
    // ********************************************
    //std::unique_ptr<Agent> player_ptr = std::make_unique<QLearningAgent>(0);
    //players.emplace_back(std::move(player_ptr));
    if(options.get_option<int>("-p")<int(2)||options.get_option<int>("-p")>int(4)){             //游戏人数不合法
        options.usage();   
        exit(0);
    }
    else if(options.get_option<int>("-p")==int(3)){         //三人游戏
        numPlayer=3;

        if(options.get_option<std::string>("-m")==std::string("SelfTrain")){      
              /////////////////////for wmz
        }

        else if(options.get_option<std::string>("-m")==std::string("HumanVsComputer")){
           int humanId=options.get_option<int>("-i");                    //人机对抗
           if(humanId<1||humanId>3){                         //玩家id不合法
                options.usage();   
                exit(0);
           }
           else{
                std::unique_ptr<Agent> player_ptr = std::make_unique<HumanAgent>(humanId-1);
                if(options.get_option<std::string>("-a")==std::string("Minimax")){
                    for(int i=0;i<3;i++){
                        if(i==humanId-1){
                            players.emplace_back(std::move(player_ptr));
                        }
                        else{
                            std::unique_ptr<Agent> agent_ptr = std::make_unique<MinimaxAgent>(i);
                            players.emplace_back(std::move(agent_ptr));
                        }
                    }
                }
                else if(options.get_option<std::string>("-a")==std::string("Greedy")){
                    for(int i=0;i<3;i++){
                        if(i==humanId-1){
                            players.emplace_back(std::move(player_ptr));
                        }
                        else{
                            std::unique_ptr<Agent> agent_ptr = std::make_unique<GreedyAgent>(i);
                            players.emplace_back(std::move(agent_ptr));
                        }
                    }
                } 
                else if(options.get_option<std::string>("-a")==std::string("QLearning")){           
                    for(int i=0;i<3;i++){
                        if(i==humanId-1){
                            players.emplace_back(std::move(player_ptr));
                        }
                        else{
                            std::unique_ptr<Agent> agent_ptr = std::make_unique<QLearningAgent>(i);
                            players.emplace_back(std::move(agent_ptr));
                        }
                    }
                }
                else{
                    options.usage();      //agent 不合法
                    exit(0);
                }
                state=GameState();
           }
        }
        else{
            options.usage();      //model 不合法
            exit(0);
        }
    }
    else if(options.get_option<int>("-p")==int(4)){         //四人游戏
        numPlayer=4;

        if(options.get_option<std::string>("-m")==std::string("SelfTrain")){
              /////////////////////for wmz
        }
        else if(options.get_option<std::string>("-m")==std::string("HumanVsComputer")){
           int humanId=options.get_option<int>("-i");
           if(humanId<1||humanId>4){                         //玩家id不合法
                options.usage();   
                exit(0);
           }
           else{
                std::unique_ptr<Agent> player_ptr = std::make_unique<HumanAgent>(humanId-1);
                if(options.get_option<std::string>("-a")==std::string("Minimax")){
                    for(int i=0;i<4;i++){
                        if(i==humanId-1){
                            players.emplace_back(std::move(player_ptr));
                        }
                        else{
                            std::unique_ptr<Agent> agent_ptr = std::make_unique<MinimaxAgent>(i);
                            players.emplace_back(std::move(agent_ptr));
                        }
                    }
                }
                else if(options.get_option<std::string>("-a")==std::string("Greedy")){
                    for(int i=0;i<4;i++){
                        if(i==humanId-1){
                            players.emplace_back(std::move(player_ptr));
                        }
                        else{
                            std::unique_ptr<Agent> agent_ptr = std::make_unique<GreedyAgent>(i);
                            players.emplace_back(std::move(agent_ptr));
                        }
                    }
                } 
                else if(options.get_option<std::string>("-a")==std::string("QLearning")){           
                    for(int i=0;i<4;i++){
                        if(i==humanId-1){
                            players.emplace_back(std::move(player_ptr));
                        }
                        else{
                            std::unique_ptr<Agent> agent_ptr = std::make_unique<QLearningAgent>(i);
                            players.emplace_back(std::move(agent_ptr));
                        }
                    }
                }
                else{
                    options.usage();      //agent 不合法
                    exit(0);
                }
                state=GameState();
           }
        }
        else{
            options.usage();      //model 不合法
            exit(0);
        }
    }
    else if (options.get_option<int>("-p")==int(2)){                                                     //两人游戏（default）
        numPlayer=2;

        if(options.get_option<std::string>("-m")==std::string("SelfTrain")){        //self train
            /////////////////////for wmz
        }

        else if(options.get_option<std::string>("-m")==std::string("HumanVsComputer")){         //人机对抗
           int humanId=options.get_option<int>("-i");
           if(humanId<1||humanId>2){                         //玩家id不合法
                options.usage();   
                exit(0);
           }
           else{
                std::unique_ptr<Agent> player_ptr = std::make_unique<HumanAgent>(humanId-1);
                if(options.get_option<std::string>("-a")==std::string("Minimax")){
                    for(int i=0;i<2;i++){
                        if(i==humanId-1){
                            players.emplace_back(std::move(player_ptr));
                        }
                        else{
                            std::unique_ptr<Agent> agent_ptr = std::make_unique<MinimaxAgent>(i);
                            players.emplace_back(std::move(agent_ptr));
                        }
                    }
                }
                else if(options.get_option<std::string>("-a")==std::string("Greedy")){
                    for(int i=0;i<2;i++){
                        if(i==humanId-1){
                            players.emplace_back(std::move(player_ptr));
                        }
                        else{
                            std::unique_ptr<Agent> agent_ptr = std::make_unique<GreedyAgent>(i);
                            players.emplace_back(std::move(agent_ptr));
                        }
                    }
                } 
                else if(options.get_option<std::string>("-a")==std::string("QLearning")){           
                    for(int i=0;i<2;i++){
                        if(i==humanId-1){
                            players.emplace_back(std::move(player_ptr));
                        }
                        else{
                            std::unique_ptr<Agent> agent_ptr = std::make_unique<QLearningAgent>(i);
                            players.emplace_back(std::move(agent_ptr));
                        }
                    }
                }
                else{
                    options.usage();      //agent 不合法
                    exit(0);
                }
                state=GameState();
            }

        }
        else{
            options.usage();      //model 不合法
            exit(0);
        }
    }
}
void Game::run(){
    /*
    While(!state.is_win())
        for p in players:
            a=p->getAction(state)
            state.apply_action(a)
    check who wins...
    */
   std::cout<<"Game start!"<<std::endl;
   // players[0]->getAction(state);

}

void Game::train(){
    // for wmz
    std::cout<<"Start training!"<<std::endl;
}