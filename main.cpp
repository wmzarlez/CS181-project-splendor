#include "util.hpp"
#include "game.h"

Options options = Options();
std::unordered_map<std::string,int> consumingTime;

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
            //update_version();
        }
    }
    else if(options.get_option<std::string>("-m")==std::string("ComputerBattle")){
        int numBattle=1;
        std::unordered_map<std::string,int> scoreBoard;
        for(int i=0;i<numBattle;i++){
            Game game;
            scoreBoard[game.battle()]+=1;
            //update_version();
        }
        std::vector<std::string> agentVector;
        for(auto i:scoreBoard){
            agentVector.push_back(i.first);
        }
        for(int i=0;i<agentVector.size();i++){
            if(i==0){
                std::cout<<agentVector[i];
            }
            else{
                std::cout<<":"<<agentVector[i];
            }
        }
        std::cout<<"=";
        for(int i=0;i<agentVector.size();i++){
            if(i==0){
                std::cout<<scoreBoard[agentVector[i]];
            }
            else{
                std::cout<<":"<<scoreBoard[agentVector[i]];
            }
        }
        std::cout<<std::endl;
        for(auto i:consumingTime){
            std::cout<<i.first<<" takes "<<i.second<<" millisecs."<<std::endl;
        }
    }
    else{
        std::cout<<"Game mode error!"<<std::endl;
    }

}