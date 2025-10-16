#pragma once
#include <iostream>
#include<vector>

template <class T>
std::vector<T> append(const std::vector<T>& first,const std::vector<T>& second) {
	std::vector<T> res;
	res.reserve(first.size() + second.size());
	res.insert(res.end(), first.begin(), first.end());
	res.insert(res.end(), second.begin(), second.end());

	return res;
}
