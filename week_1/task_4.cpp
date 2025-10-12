#include <iostream>
#include <utility>


void printPermutation(const int* a, int n) {
	for (int i = 0;i < n;++i)
		std::cout << a[i] << (i + 1 == n ? '\n' : ' ');
}

void permutate(int* a, int start, int end) {
	if (start == end)
		printPermutation(a, end + 1);

	for (int i = start;i <= end;i++) {
		std::swap(a[start], a[i]);

		permutate(a, start + 1, end);

		std::swap(a[start], a[i]);
	}
}