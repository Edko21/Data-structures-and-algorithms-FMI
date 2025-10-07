#pragma once

template <class T>
void Merge(T* firstArr, size_t firstSize, T* secondArr, size_t secondSize, T* resArr) {
	size_t resIter = 0;
	size_t firstIter = 0;
	size_t secondIter = 0;

	while (firstIter < firstSize && secondIter < secondSize)
		resArr[resIter++] = (firstArr[firstIter] <= secondArr[secondIter] ? firstArr[firstIter++] : secondArr(secondIter++));
	while (firstIter < firstSize)
		resArr[resIter++] = firstArr[firstIter++];
	while (secondIter < secondSize)
		resArr[resIter++] = secondArr[secondIter++];
}

template <class T>
void mergeSortStep(T* pArr, size_t Size, T* pBuff) {
	if (Size <= 1)
		return;
	size_t mid = Size / 2;
	mergeSortStep(pArr, mid, pBuff);
	mergeSortStep(pArr + mid, Size - mid, pBuff + mid);
	Merge(pArr, mid, pArr + mid, Size - mid, pBuff);

	for (size_t i = 0;i < Size;i++)
		pArr[i] = pBuff[i];
}

template <class T>
void mergeSort(T* pArr, size_t Size) {
	if (!pArr || Size == 0)
		return;
	T* pBuff = new T[Size];
	mergeSortStep(pArr, Size, pBuff);
	delete[] pBuff;
}

