#include "util.hpp"
#include "game.h"

Options options = Options();

int main(int argc, const char* argv[]){

    options.set_args(argc, argv);

    Game game;
    
    if(options.get_option<std::string>("-m")==std::string("HumanVsComputer")){
        game.run();
    }
    else if(options.get_option<std::string>("-m")==std::string("SelfTrain")){
        game.train();
    }
    else{
        std::cout<<"Game mode error!"<<std::endl;
    }

}