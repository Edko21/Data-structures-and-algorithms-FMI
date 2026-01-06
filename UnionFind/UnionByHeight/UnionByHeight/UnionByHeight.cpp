#include <iostream>
#include "UnionByHeight.h"

UnionFind::UnionFind(int n) :parent(n), height(n, 0) {
	for (int i = 0;i < n;i++) {
		parent[i] = i;
	}
}

int UnionFind::getRoot(int n) {
	if (parent[n] != n) {
		parent[n] = getRoot(parent[n]);
	}
	return parent[n];
}

bool UnionFind::areInOneSet(int n, int k) {
	return getRoot(n) == getRoot(k);
}

bool UnionFind::Union(int n, int k) {
	int root1 = getRoot(n);
	int root2 = getRoot(k);

	if (root1 == root2) {
		return false;
	}

	if (height[root1] < height[root2]) {
		parent[root1] = root2;
	}
	else if (height[root1] > height[root2]) {
		parent[root2] = root1;
	}
	else {
		parent[root2] = root1;
		height[root1]++;
	}
	return true;
}

int main(){
	UnionFind uf(10);

	std::cout << "Union(1, 2): " << uf.Union(1, 2) << std::endl;
	std::cout << "Union(2, 3): " << uf.Union(2, 3) << std::endl;
	std::cout << "Union(4, 5): " << uf.Union(4, 5) << std::endl;
	std::cout << "Union(6, 7): " << uf.Union(6, 7) << std::endl;
	std::cout << "Union(5, 6): " << uf.Union(5, 6) << std::endl;
	std::cout << "Union(3, 7): " << uf.Union(3, 7) << std::endl;

	std::cout << "areInOneSet(1, 7): " << uf.areInOneSet(1, 7) << std::endl;
	std::cout << "areInOneSet(4, 6): " << uf.areInOneSet(4, 6) << std::endl;
	std::cout << "areInOneSet(1, 4): " << uf.areInOneSet(1, 4) << std::endl;
	std::cout << "areInOneSet(8, 9): " << uf.areInOneSet(8, 9) << std::endl;

	return 0;
}