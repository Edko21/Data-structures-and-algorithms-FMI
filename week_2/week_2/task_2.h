#pragma once
#include <vector>
#include <algorithm>

template<class T>
std::vector<T> union1(const std::vector<T>& first,const std::vector<T>& second) {
	std::vector<T> res;
	for (const T& el : first) {
		if (std::find(res.begin(), res.end(), el) == res.end())
			res.push_back(el);
	}

	for (const T& el : second) {
		if (std::find(res.begin(), res.end(), el) == res.end())
			res.push_back(el);
	}

	return res;
}