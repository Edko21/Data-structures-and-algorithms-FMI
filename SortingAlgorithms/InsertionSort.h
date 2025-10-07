#pragma once

template <class T>
void insertionSort(T* arr, int len) {
	for (int i = 1;i < len;i++) {
		T el = arr[i];
		int ind = i - 1;
		while (ind >= 0 && arr[ind] > el) {
			arr[ind + 1] = arr[ind];
			ind--;
		}
		arr[ind + 1] = el;
	}
}