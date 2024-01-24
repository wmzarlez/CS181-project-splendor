#include <chrono>
#include "game.h"
#include "humanAgent.h"
#include "minimaxAgent.h"
#include "qLearningAgent.h"
#include "greedyAgent.h"
#include "randomAgent.h"

extern Options options;
extern std::unordered_map<std::string,int> consumingTime;

Game::Game(){
    
    numPlayer=options.get_option<int>("-p");
    if(numPlayer<int(2)||numPlayer>int(4)){             //游戏人数不合法
        options.usage();   
        exit(1);
    }
    else{
        if(options.get_option<std::string>("-m")==std::string("SelfTrain")){      
            int qAgentIndex=rand()%numPlayer;
            std::unique_ptr<Agent> q_ptr = std::make_unique<QLearningAgent>(qAgentIndex);
            //std::unique_ptr<Agent> q_ptr = std::make_unique<GreedyAgent>(qAgentIndex);
            for(int i=0;i<numPlayer;i++){
                if(i==qAgentIndex){
                    players.emplace_back(std::move(q_ptr));
                    std::cout<<"Q-Learning Agent is player "<<qAgentIndex+1<<std::endl;
                }
                else{
                    //std::unique_ptr<Agent> trainer_ptr = std::make_unique<RandomAgent>(i);
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
                if(options.get_option<std::string>("-a")==std::string("AdversarialSearch")){
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
                //state=GameState();
           }
        }
        else if(options.get_option<std::string>("-m")==std::string("ComputerBattle")){      
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
        else{
            options.usage();      //model 不合法
            exit(1);
        }
    }
}
void Game::run(){
    bool noTerminalOutputs=options.get_option<bool>("-no-terminal-outputs");
    state.print_table();

    while(!state.is_win()){
        state.numTurn++;
        std::cout<<std::endl<<"Turn "<<state.numTurn<<" Start"<<std::endl;
        for (int i=0;i<numPlayer;i++){
            std::cout<<std::endl;
            std::cout<<"Player "<<i+1<<"'s turn:"<<std::endl;
            Action turnAction = (*(players[i].get())).getAction(state);
            state.apply_action(turnAction,i);
            state.print_table();
            //getchar();
        }
    }
    std::cout<<"Game over"<<std::endl;
    // players[0]->getAction(state);
}

void Game::train(){
     while(!state.is_win()){
        state.numTurn++;
        std::cout<<std::endl<<"Turn "<<state.numTurn<<" Start"<<std::endl;
        for (int i=0;i<numPlayer;i++){
            //std::cout<<std::endl;
            //std::cout<<"Player "<<i+1<<"'s turn:"<<std::endl;
            Action turnAction = (*(players[i].get())).getAction(state);
            state.apply_action(turnAction,i);
            //state.print_table();
            //getchar();
        }
    }
    std::cout<<"Game over"<<std::endl;
}

std::string Game::battle(){
    int winnerId=0;
     while(!winnerId){
        state.numTurn++;
        std::cout<<std::endl<<"Turn "<<state.numTurn<<" Start"<<std::endl;
        for (int i=0;i<numPlayer;i++){
            std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
            Action turnAction = (*(players[i].get())).getAction(state);
            state.apply_action(turnAction,i);
            consumingTime[players[i]->get_name()]+=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
            //getchar();
        }
        winnerId=state.who_wins();
    }
    std::cout<<"Game over"<<std::endl;
    return players[winnerId-1]->get_name();
}