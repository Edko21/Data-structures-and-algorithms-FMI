#pragma once
#include <vector>
#include <algorithm> 

template <typename T>
std::vector<T> intersection(const std::vector<T>& first, const std::vector<T>& second){
    std::vector<T> result;

    for (const T& elem : first){
        if (std::find(second.begin(), second.end(), elem) != second.end() && std::find(result.begin(), result.end(), elem) == result.end()){
            result.push_back(elem);
        }
    }
    return result;
}
