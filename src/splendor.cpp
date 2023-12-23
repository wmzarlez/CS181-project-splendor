#include "splendor.h"

PlayerBoard::PlayerBoard(){
    
}

GameState::GameState(){
    
}

std::vector<Action> GameState::get_legal_action(int playerIndex){
    
}

bool GameState::apply_action(Action action){
    
}

bool GameState::is_win(){
    
}

void GameState::check_noble(int playerIndex){

}

void GameState::add_card_random(int cardLevel, int cardIndex){

}
void GameState::add_card_explicit(int cardLevel, int cardIndex, int cardId){

}
void GameState::remove_card(int cardLevel, int cardIndex){

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