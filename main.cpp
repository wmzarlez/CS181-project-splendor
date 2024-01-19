#include "util.hpp"
#include "game.h"

Options options = Options();

void update_version(){
    std::ifstream version("../qTrainingLog/version.txt");
    std::string line;
    if(!version.is_open()){
        return;
    }
    std::getline(version,line);
    int bestModel=atoi(line.c_str());
    std::getline(version,line);
    int latestModel=atoi(line.c_str());
    version.close();

    std::ofstream out("../qTrainingLog/version.txt",std::ios::out);
    if(!out.is_open()){
        return;
    }
    out<<bestModel+1<<std::endl;
    out<<latestModel+1<<std::endl;
    return;
}

int main(int argc, const char* argv[]){

    srand((unsigned) time(NULL));
    options.set_args(argc, argv);

    if(options.get_option<std::string>("-m")==std::string("HumanVsComputer") ||
        options.get_option<std::string>("-m")==std::string("ComputerBattle")){
        Game game;
        game.run();
    }
    else if(options.get_option<std::string>("-m")==std::string("SelfTrain")){
        int numTrain=options.get_option<int>("-n");
        numTrain=1;
        for(int i=0;i<numTrain;i++){
            Game game;
            game.train();
            //update_version();
        }
    }
    else{
        std::cout<<"Game mode error!"<<std::endl;
    }

}