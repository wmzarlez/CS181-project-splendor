#include "humanAgent.h"

extern Options options;

HumanAgent::HumanAgent(int index): playerIndex(index){}

std::uint16_t HumanAgent::getGemAvailable(const GameState& state) const{
  std::uint16_t total = 0;
  for(std::uint16_t i=0; i<6; total += state.playerBoards[playerIndex].gemsOwnwd[i++]);
  return total;
}

bool HumanAgent::isLegalAction(const GameState& state, const Action myAction) const{
  if(myAction.type == ActionType::SELECTGEMS){
    if(myAction.params[0]<6 && myAction.params[0]==myAction.params[1] && myAction.params[0]==myAction.params[2]){return false;}
    int getGemCount[5] = {0};
    int doubleGemCnt = 0;
    int gameStateGem[6]; memcpy(reinterpret_cast<void*>(gameStateGem), reinterpret_cast<const void*>(state.gemPile), 6*sizeof(int));
    int playerGem[6]; memcpy(reinterpret_cast<void*>(playerGem), reinterpret_cast<const void*>(state.playerBoards[playerIndex].gemsOwnwd), 6*sizeof(int));
    for(std::uint16_t i=0; i<3; ++i){
      if(myAction.params[i] == Gem::BLANK_) continue;
      else if(myAction.params[i] == Gem::YELLOW) return false;
      else if(!gameStateGem[myAction.params[i]]) return false;
      else{
        ++getGemCount[myAction.params[i]];
        --gameStateGem[myAction.params[i]];
      }
    }
    for(std::uint16_t i=0; i<5; ++i) if(getGemCount[i] > 2) doubleGemCnt += 1;
    if(doubleGemCnt > 1) return false;
    for(std::uint16_t i=0; i<6; playerGem[i] += getGemCount[i], ++i);
    for(std::uint16_t i=0; i<6; ++i){
      if(myAction.params[i] == Gem::BLANK_) continue;
      if(!playerGem[myAction.params[i]]) return false;
      else --playerGem[myAction.params[i]];
    }
    return true;
  }

  else if(myAction.type == ActionType::BUYCARD){
    int playerGem[6]; memcpy(reinterpret_cast<void*>(playerGem), reinterpret_cast<const void*>(state.playerBoards[playerIndex].gemsOwnwd), 6*sizeof(int));
    for(int i=0;i<5;i++){
      playerGem[i]+=state.playerBoards[playerIndex].bonuses[i];
    }
    if(myAction.params[0] >= 0 && myAction.params[0] <= 2 && myAction.params[1] >=0 && myAction.params[1] <= 3){
      if(!state.market[myAction.params[0]][myAction.params[1]].cardId) return false;
      int cardCost[5]; memcpy(reinterpret_cast<void*>(cardCost), reinterpret_cast<const void*>(state.market[myAction.params[0]][myAction.params[1]].cost), 5*sizeof(int));
      int lack = 0; // Append BONUS!
      for(std::uint16_t i=0; i<5; ++i) lack += ((playerGem[i] - cardCost[i]) >= 0 ? 0: cardCost[i] - playerGem[i]);
      if(lack > playerGem[5]) return false;
      return true;
    }
    else if(myAction.params[0] == 3 && myAction.params[1] >=0 && myAction.params[1] <= 2){
      if(!state.playerBoards[playerIndex].reservedCards[myAction.params[1]].cardId) return false;
      int cardCost[5]; memcpy(reinterpret_cast<void*>(cardCost), reinterpret_cast<const void*>(state.playerBoards[playerIndex].reservedCards[myAction.params[1]].cost), 5*sizeof(int));
      int lack = 0;
      for(std::uint16_t i=0; i<5; ++i) lack += (playerGem - cardCost) >= 0? 0: cardCost - playerGem;
      if(lack > playerGem[5]) return false;
      return true;
    }
    return false;
  }

  else if(myAction.type == ActionType::RESERVECARD){
    int playerGem[6]; memcpy(reinterpret_cast<void*>(playerGem), reinterpret_cast<const void*>(state.playerBoards[playerIndex].gemsOwnwd), 6*sizeof(int));
    if(myAction.params[0] >= 0 && myAction.params[0] <= 2 && myAction.params[1] >=0 && myAction.params[1] <= 3 && state.market[myAction.params[0]][myAction.params[1]].cardId){}
    else return false;
    if(myAction.params[2] == 1 && getGemAvailable(state) == 10){
      if(myAction.params[3] < 0 || myAction.params[3] > 5) return false;
      if(myAction.params[3] == Gem::YELLOW) return true;
      else if(playerGem[myAction.params[3]] == 0) return false;
    }
  }
  return true;
}

Action HumanAgent::getAction(const GameState& state){
  Action myAction; 
  for(;;){
    myAction = Action();
    int myActionType = -1;
    do{
      std::cout << "Enter action type:\n\tSELECT GEMS  -> 0\n\tBUY CARD     -> 1\n\tRESERVE CARD -> 2\n\tSKIP         -> 3.\n";
      std::cin >> myActionType;
    } while(myActionType<0 || myActionType>3);

    myAction.type = static_cast<ActionType>(myActionType);
    if(myActionType == ActionType::SELECTGEMS){
      std::uint16_t gemNum = getGemAvailable(state);
      for(std::uint16_t i=0; i<6; myAction.params[i++] = Gem::BLANK_);
      std::cout << "Enter gem type:\n\tWHITE     -> 0\n\tBLUE      -> 1\n\tGREEN     -> 2\n\tRED       -> 3\n\tBLACK     -> 4\n\tNONE      -> 6.\n";
      for(std::uint16_t i=0; i<3; ++i){
        std::cin >> myAction.params[i];
        if(myAction.params[i] != Gem::BLANK_) gemNum += 1;
      }
      if(gemNum > 10){
        std::cout << "Too much gems, enter " << gemNum - 10 << " gems:\n\tWHITE     -> 0\n\tBLUE      -> 1\n\tGREEN     -> 2\n\tRED       -> 3\n\tBLACK     -> 4\n\tYELLOW    -> 5.\n";
        for(std::uint16_t i=3; i<gemNum-7; std::cin >> myAction.params[i++]);
        gemNum = 10;
      }
    }
    else if(myActionType == ActionType::BUYCARD){
      std::cout << "Enter coordinates(cardLevel(if you want to bug a reserved card, enter 4) and cardColumn):\n";
      int cardLevel;
      int cardColumn;
      std::cin >> cardLevel >> cardColumn;
      myAction.params[0]=cardLevel-1;
      myAction.params[1]=cardColumn-1;
    }
    else if(myActionType == ActionType::RESERVECARD){
      std::uint16_t gemNum = getGemAvailable(state);
      myAction.params[2] = Gem::BLANK_;
      std::cout << "Enter coordinates(cardLevel and cardColumn), then enter 1 if want to choose a golden gem and 0 otherwise:\n";
      int cardLevel;
      int cardColumn;
      std::cin >> cardLevel >> cardColumn >> myAction.params[2];
      myAction.params[0]=cardLevel-1;
      myAction.params[1]=cardColumn-1;
      if(myAction.params[2] == 1 && gemNum >= 10){
        std::cout << "Too much gems, throw one gem:\n\tWHITE     -> 0\n\tBLUE      -> 1\n\tGREEN     -> 2\n\tRED       -> 3\n\tBLACK     -> 4\nYELLOW    -> 5.\n";
        std::cin >> myAction.params[3];
      }
    }
    if(isLegalAction(state, myAction)) break;
    else std::cout << "ILLEGAL ACTION\n";
  }
  return myAction;
}