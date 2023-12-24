#include "game.h"
#include "humanAgent.h"
#include "minimaxAgent.h"
#include "qLearningAgent.h"

extern Options options;

Game::Game(){
    // init every menber value
    // ********************************************
    // e.g.
    // // player 1
    // std::unique_ptr<Agent> player_ptr = std::make_unique<HumanAgent>();
    // players.emplace_back(std::move(player_ptr));
    // ********************************************
    std::unique_ptr<Agent> player_ptr = std::make_unique<QLearningAgent>(0);
    players.emplace_back(std::move(player_ptr));

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