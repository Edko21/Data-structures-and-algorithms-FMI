#pragma once
#include <iostream>

template <class T>
void bubbleSort(T* arr, unsigned len) {
	unsigned end = len - 1;
	for (int i = 0;i < len - 1;i++) {
		unsigned lastSwappedInd = 0;
		for (int j = 0;j < end;j++) {
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				lastSwappedInd = j;
			}
		}
		end = lastSwappedInd;
		if (lastSwappedInd == 0)
			return;
	}
}