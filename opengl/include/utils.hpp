#pragma once

#include <iostream>
#include <format>
#include <string>

template<typename T, std::size_t N>
constexpr std::array<T, N> operator-(std::array<T, N> data) {
    for(auto i = 0ULL ; i < N ; ++i) {
        data[i] = -data[i];
    }
    return data;
}

inline void runtime_error(const char* file, unsigned int line, const std::string& what) {
    std::cerr << std::format("Runtime Error happened in {}:{}\n\t{}", file, line, what) << std::endl;
}

#define error(what) runtime_error(__FILE__, __LINE__, what)

template<typename T, typename... Args, typename Func>
inline void apply(Func&& func, T&& first, Args&&... others) {
    func(first);
    if constexpr (sizeof...(others) > 0) {
        apply(std::forward<Func>(func), std::forward<Args>(others)...);
    }
}

template<long Begin, long Step, long End, typename Func>
inline void static_for(Func&& func) {
    if constexpr (Begin < End) {
        func(Begin);
        static_for<Begin + Step, Step, End>(std::forward<Func>(func));
    }
}