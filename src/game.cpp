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
    
    numPlayer=options.get_option<int>("-p");
    if(numPlayer<int(2)||numPlayer>int(4)){             //游戏人数不合法
        options.usage();   
        exit(1);
    }
    else{
        if(options.get_option<std::string>("-m")==std::string("SelfTrain")){      
            int qAgentIndex=rand()%numPlayer;
            std::unique_ptr<Agent> q_ptr = std::make_unique<QLearningAgent>(qAgentIndex);
            for(int i=0;i<numPlayer;i++){
                if(i==qAgentIndex){
                    players.emplace_back(std::move(q_ptr));
                }
                else{
                    std::unique_ptr<Agent> trainer_ptr = std::make_unique<GreedyAgent>(i);
                    players.emplace_back(std::move(trainer_ptr));
                }
            }
        }
        else if(options.get_option<std::string>("-m")==std::string("HumanVsComputer")){
           int humanId=options.get_option<int>("-i");                    //人机对抗
           if(humanId<1||humanId>numPlayer){                         //玩家id不合法
                options.usage();   
                exit(1);
           }
           else{
                std::unique_ptr<Agent> player_ptr = std::make_unique<HumanAgent>(humanId-1);
                if(options.get_option<std::string>("-a")==std::string("Minimax")){
                    for(int i=0;i<numPlayer;i++){
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
                    for(int i=0;i<numPlayer;i++){
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
                    for(int i=0;i<numPlayer;i++){
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
                    exit(1);
                }
                state=GameState();
           }
        }
        else{
            options.usage();      //model 不合法
            exit(1);
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
    bool noTerminalOutputs=options.get_option<bool>("-no-terminal-outputs");
    if(!noTerminalOutputs)state.print_table();

    while(!state.is_win()){
        state.numTurn++;
        for (int i=0;i<numPlayer;i++){
            Action turnAction = (*(players[i].get())).getAction(state);
            state.apply_action(turnAction,i);
            if(!noTerminalOutputs)state.print_table();
        }
    }
    std::cout<<"Game over"<<std::endl;
    // players[0]->getAction(state);
}

void Game::train(){
    // for wmz
     while(!state.is_win()){
        state.numTurn++;
        for (int i=0;i<numPlayer;i++){
            Action turnAction = (*(players[i].get())).getAction(state);
            state.apply_action(turnAction,i);
        }
    }
    std::cout<<"Game over"<<std::endl;
}