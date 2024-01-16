#include "humanAgent.h"

extern Options options;

HumanAgent::HumanAgent(int index): playerIndex(index){}

std::uint16_t HumanAgent::getGemAvailable(const GameState& state) const{
  std::uint16_t total = 0;
  for(std::uint16_t i=0; i<6; total += state.playerBoards[playerIndex].gemsOwnwd[i++]);
  return total;
}

bool isLegalAction(const GameState& state, const Action myAction){
  int gameStateGem[6]; memcpy(reinterpret_cast<void*>(gameStateGem), reinterpret_cast<const void*>(state.gemPile), 6*sizeof(int));
  if(myAction.type == ActionType::SELECTGEMS){
    int getGemCount[5] = {0};
    for(std::uint16_t i=0; i<3; ++i){
      if(myAction.params[i] == Gem::BLANK_) continue;
      else if(myAction.params[i] == Gem::YELLOW) return false;
      else if(!gameStateGem[myAction.params[i]]) return false;
      else{
        ++getGemCount[myAction.params[i]];
        -- gameStateGem[myAction.params[i]];
      }
    }

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

Action HumanAgent::getAction(const GameState& state) const{
  std::uint16_t gemNum = getGemAvailable(state);
  Action myAction = Action();
  int myActionType = -1;
  for(;;){
    do{
      std::cout << "Enter action type:\n\tSELECT GEMS  -> 0\n\tBUY CARD     -> 1\n\tRESERVE CARD -> 2\n\tSKIP         -> 3.\n";
      std::cin >> myActionType;
    } while(myActionType<0 || myActionType>3);

    myAction.type = static_cast<ActionType>(myActionType);
    if(myActionType == ActionType::SELECTGEMS){
      for(std::uint16_t i=0; i<6; myAction.params[i++] = Gem::BLANK_);
      std::cout << "Enter gem type:\n\tWHITE     -> 0\n\tBLUE      -> 1\n\tGREEN     -> 2\n\tRED       -> 3\n\tBLACK     -> 4\n\tYELLOW    -> 5\n\tNONE      -> 6.\n";
      for(std::uint16_t i=0; i<3; ++i){
        std::cin >> myAction.params[i];
        if(myAction.params[i] != Gem::BLANK_) gemNum += 1;
      }
      if(gemNum > 10){
        std::cout << "Too much gems, enter " << gemNum - 10 << " gems:\n\tWHITE     -> 0\n\tBLUE      -> 1\n\tGREEN     -> 2\n\tRED       -> 3\n\tBLACK     -> 4\nYELLOW    -> 5.\n";
        for(std::uint16_t i=3; i<gemNum-7; std::cin >> myAction.params[i++]);
        gemNum = 10;
      }
    }
    else if(myActionType == ActionType::BUYCARD){
      std::cout << "Enter coordinates(cardLevel and cardIndex):\n";
      std::cin >> myAction.params[0] >> myAction.params[1];
    }
    else if(myActionType == ActionType::RESERVECARD){
      myAction.params[2] = Gem::BLANK_;
      std::cout << "Enter coordinates(cardLevel and cardIndex), then enter 1 if want to choose a golden gem and 0 otherwise:\n";
      std::cin >> myAction.params[0] >> myAction.params[1] >> myAction.params[2];
      if(myAction.params[2] == 1 && gemNum >= 10){
        std::cout << "Too much gems, throw one gem:\n\tWHITE     -> 0\n\tBLUE      -> 1\n\tGREEN     -> 2\n\tRED       -> 3\n\tBLACK     -> 4\nYELLOW    -> 5.\n";
        std::cin >> myAction.params[3];
      }
    }
    if(isLegalAction(state, myAction)) break;
    else std::cout << "ILLEGAL ACTION\n";
  }
}