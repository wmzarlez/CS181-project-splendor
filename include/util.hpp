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

class Options {
    private:
        std::unordered_map<std::string, std::optional<std::string>> _options;

        std::string exe_name;

        
        inline bool is_flag(const char* s) {
            return (strlen(s) > 0 && s[0] == '-');
        }

    public:
        Options() = default;

        inline void set_args(int argc, const char* argv[]) {
            if(!argc)
                throw std::invalid_argument("argc should be a positive integer!");

            int curr = 1;
            while(curr < argc) {
                if(is_flag(argv[curr])) {
                    int next = curr + 1;
                    if(next < argc && !is_flag(argv[next])) {
                        _options[argv[curr]] = argv[next];
                        curr += 2;
                    } else {
                        _options[argv[curr++]] = std::nullopt;
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
inline std::optional<int> Options::get_option<int>(const char* s) const {
    auto iter = _options.find(s);
    int ret;
    if(iter == _options.end() || !(iter->second) || sscanf(iter->second->c_str(), "%d", &ret) < 1)
        return std::nullopt;
    return ret;
}