#pragma once
#include <iostream>

template <typename T>
size_t partition(T* arr, size_t len) {
	T pivot = [len / 2];
	int i = 0;
	int j = len - 1;

	while (true) {
		while (arr[i] < pivot) {
			i++;
		}
		while (arr[j] > pivot) {
			j--;
		}
		if (arr[i] == arr[j]) {
			i++;
		}
		if (i < j) {
			std::swap(arr[i], arr[j]);
		}
		else {
			return j;
		}
	}
}

template<typename T>
void quickSort(T* arr, size_t len) {
	if (len <= 1)
		return;
	size_t pivotInd = partition(arr, len);
	quickSort(arr, pivotInd);
	quickSort(arr + pivotInd + 1, len - pivotInd - 1);
}
