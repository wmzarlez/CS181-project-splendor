#include "humanAgent.h"

extern Options options;

HumanAgent::HumanAgent(int index): playerIndex(index){}

bool isLegalAction(const Action myAction, const GameState& state, int playerIndex){
  int gamestateGem[6] = {2,1,0,3,5,0}; 
  int playerGem[6] = {1,0,1,1,1,6};
  int cardGemCost[5] = {1,1,1,0,2}; 

  if(myAction.type<0 || myAction.type>3) return false;
  if(myAction.type == ActionType::SELECTGEMS){
    for(short i=0; i<3; ++i){
      if(gamestateGem[myAction.params[i]] == 0) return false;
      else{
        --gamestateGem[myAction.params[i]];
        ++playerGem[myAction.params[i]];
      }
    }
    for(short i=3; i<6; ++i){
      if(myAction.params[i] == Gem::BLANK_) continue;
      else{
        if(playerGem[myAction.params[i]] == 0) return false;
        else --playerGem[myAction.params[i]];
      }
    }
    return true;
  }

  else if(myAction.type == ActionType::BUYCARD){
    for(short i=0; i<5; ++i){
      if(playerGem[i] < cardGemCost[i]){
        cardGemCost[i] -= playerGem[i];
        playerGem[i] = 0;
      }
      else{
        playerGem[i] -= cardGemCost[i];
        cardGemCost[i] = 0;
      }
    }
    int tmpLackGem = 0;
    for(auto i=0; i<5; tmpLackGem += cardGemCost[i++]);
    if(playerGem[5] < tmpLackGem) return false;
    else return true;
  }

  else if(myAction.type == ActionType::RESERVECARD){
    playerGem[5] += 1; 
    if(myAction.params[2] != Gem::BLANK_){
      if(playerGem[myAction.params[2]] == 0) return false;
      else return true;
    }
  }
  else if(myAction.type == ActionType::SKIP) return true;
  return true;
}

Action HumanAgent::getAction(const GameState& state){
    while(true){
      int cardCount = 10; 
      Action myAction = Action(); // From input extract an action; now only consults for necessary parameters, validity is checked later.

      // Extracting action type.
      int actionType = -1; 
      do{
        std::cout << "Enter action type:\n" 
                                          << "SELECT GEMS  -> 0\n"
                                          << "BUY CARD     -> 1\n"
                                          << "RESERVE CARD -> 2\n"
                                          << "SKIP         -> 3.\n";
        std::cin >> actionType;
        // if(std::cin.fail()) std::cin.clear(); 
      } while(actionType<0 || actionType >3);
      
      if(actionType == ActionType::SELECTGEMS){
          myAction.type == ActionType::SELECTGEMS;
          for(short i=0; i<6; myAction.params[i++]=Gem::BLANK_);
          std::cout << "Enter three different gem type:\n" 
                                          << "WHITE       -> 0\n"
                                          << "BLUE        -> 1\n"
                                          << "GREEN       -> 2\n"
                                          << "RED         -> 3\n"
                                          << "BLACK       -> 4\n"
                                          << "YELLOW      -> 5.\n";
          
          for(short i=0; i<3; ++i){
            std::cin >> myAction.params[i]; 
            if(myAction.params[i] != Gem::BLANK_) cardCount += 1; 
          }
          
          if(cardCount > 10){
            std::cout << "Too much gems, enter " << cardCount - 10 << " gems:\n" 
                                          << "WHITE       -> 0\n"
                                          << "BLUE        -> 1\n"
                                          << "GREEN       -> 2\n"
                                          << "RED         -> 3\n"
                                          << "BLACK       -> 4\n"
                                          << "YELLOW      -> 5.\n";
            
            for(short i=3; i<3+cardCount-10; std::cin >> myAction.params[i++]); 
            cardCount = 10;

          }
          
      }
      else if(actionType == ActionType::BUYCARD){
        myAction.type == ActionType::BUYCARD;
        std::cout << "Enter card level and card index: ";
        for(short i=0; i<2; std::cin >> myAction.params[i++]); // The remaining params are useless, doesn't indicate any meaning.
      }
      else if(actionType == ActionType::RESERVECARD){
        myAction.type == ActionType::RESERVECARD;
        std::cout << "Enter card level and card index: ";
        myAction.params[3] = Gem::BLANK_;
        for(short i=0; i<2; std::cin >> myAction.params[i++]);
        if(cardCount == 10) {
          std::cout << "Too much gems, enter 1 gem:\n"
                                          << "WHITE       -> 0\n"
                                          << "BLUE        -> 1\n"
                                          << "GREEN       -> 2\n"
                                          << "RED         -> 3\n"
                                          << "BLACK       -> 4\n"
                                          << "YELLOW      -> 5.\n";
        }
        std::cin >> myAction.params[3];
      }

      else if(actionType == ActionType::SKIP){
        myAction.type == ActionType::SKIP;
      }

      if(isLegalAction(myAction, state, playerIndex)){ 
        std::cout << "Is a legal action.\n";
        break;
      }
      else std::cout << "Not a legal action.\n";
    }
}