#include "splendor.h"

extern Options options;

PlayerBoard::PlayerBoard(){
    
}

GameState::GameState(): cardPile(std::make_shared<CardPile>()){
    
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