#pragma once
#include <cmath>
#include <numbers>
#include <optional>
#include <unordered_map>
#include <cstring>
#include <string>
#include <iostream>
#include <stdexcept>
#include <assert.h>
#include <format>

class Options {
    private:
        std::unordered_map<std::string, std::optional<std::string>> _options;

        inline bool is_flag(const char* s) {
            return (strlen(s) > 0 && s[0] == '-');
        }

    public:
        void usage(){
            std::cout<<"Usage: main.exe [options]"<<std::endl;
            std::cout<<"Options:"<<std::endl;
            std::cout<<std::format("{:<20}{}","-h/-help","Display specific types of command line options.")<<std::endl;
            std::cout<<std::format("{:<20}{}","-p","Set the number of players. ([2(default)/3/4])")<<std::endl;
            std::cout<<std::format("{:<20}{}","-m","Set the game mode. [SelfTrain/HumanVsComputer(default)]")<<std::endl;
            std::cout<<std::format("{:<20}{}","-no-graphics","Close the GUI.")<<std::endl;
            std::cout<<std::format("{:<20}{}","-no-terminal-outputs  ","Reduce most of the terminal outputs.")<<std::endl;
            std::cout<<std::format("{:<20}{}","-a","Set the agent of conmputers. [Minimax/QLearning(default)]")<<std::endl;
            std::cout<<std::format("{:<20}{}","-n","Set the number of trainings in SelfTrain mode.")<<std::endl;
            std::cout<<std::format("{:<20}{}","-s","Set your seat/the player index of human in HumanVsComputer mode. [1(default)/2/3/4](the number should be less than the number of players)")<<std::endl;
            std::cout<<std::format("{:<20}{}","-b","Set the address of the best params of approximate Q-Learning.")<<std::endl;
            std::cout<<std::format("{:<20}{}","-o","Set the address to store new params of approximate Q-Learning.")<<std::endl;
            std::cout<<std::format("{:<20}{}","-no-training","Don't update the params of approximate Q-Learning.")<<std::endl;
        }

        Options(){
            _options["-p"]="2";
            _options["-m"]="HumanVsComputer";
            _options["-no-graphyics"]="0";
            _options["-no-terminal-outputs"]="0";
            _options["-a"]="QLearning";

            // if SelfTrain
            _options["-n"]="10";

            // if HumanVSComputer
            _options["-s"]="1";

            // if Qlearning
            _options["-no-training"]="0";
            // these two option will be specified later
            _options["-b"]="./qTrainingLog";
            _options["-o"]="./qTrainingLog";

        }

        inline void set_args(int argc, const char* argv[]) {
            if(!argc)
                throw std::invalid_argument("argc should be a positive integer!");

            int curr = 1;
            
            if((argc>=2) && (strcmp(argv[1],"-h") || strcmp(argv[1],"-help"))){
                usage();
                exit(0);
            }

            while(curr < argc) {
                if(is_flag(argv[curr])) {
                    int next = curr + 1;
                    if(next < argc && !is_flag(argv[next])) {
                        _options[argv[curr]] = argv[next];
                        curr += 2;
                    } else {
                        _options[argv[curr++]] = "1";
                    }
                } else {
                    throw std::invalid_argument("argv is not valid");
                }
            }
        }

        template<typename T>
        inline std::optional<T> get_option(const char* s) const {
            static_assert(0, "Type is not supported!");
            return std::nullopt;
        }
};

template<>
inline std::optional<std::string> Options::get_option<std::string>(const char* s) const {
    auto iter = _options.find(s);
    if(iter == _options.end() || !(iter->second))
        return std::nullopt;
    return iter->second;
}

template<>
inline std::optional<int> Options::get_option<int>(const char* s) const {
    auto iter = _options.find(s);
    int ret;
    if(iter == _options.end() || !(iter->second) || sscanf(iter->second->c_str(), "%d", &ret) < 1)
        return std::nullopt;
    return ret;
}

template<>
inline std::optional<bool> Options::get_option<bool>(const char* s) const {
    auto iter = _options.find(s);
    int value;
    if(iter == _options.end())
        return std::nullopt;
    sscanf(iter->second->c_str(), "%d", &value);
    if(value==0){
        return false;
    }
    else{
        return true;
    }
}