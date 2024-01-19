#include "util.hpp"
#include "game.h"

Options options = Options();

int main(int argc, const char* argv[]){

    srand((unsigned) time(NULL));
    options.set_args(argc, argv);

    if(options.get_option<std::string>("-m")==std::string("HumanVsComputer")){
        Game game;
        game.run();
    }
    else if(options.get_option<std::string>("-m")==std::string("SelfTrain")){
        int numTrain=options.get_option<int>("-n");
        numTrain=1;
        for(int i=0;i<numTrain;i++){
            Game game;
            game.train();
        }
    }
    else{
        std::cout<<"Game mode error!"<<std::endl;
    }

}