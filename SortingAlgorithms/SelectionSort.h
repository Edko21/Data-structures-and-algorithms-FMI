#pragma once
#include <iostream>

template <typename T>
void selectionSort(T* arr, size_t size) {
	for (int i = 0;i < size-1;i++) {
		int minElInd = i;
		for (int j = i + 1;j < size;j++) {
			if (arr[j] < arr[minElInd])
				minElInd = j;
		}
		if (i != minElInd)
			std::swap(arr[i], arr[minElInd]);
	}
}
