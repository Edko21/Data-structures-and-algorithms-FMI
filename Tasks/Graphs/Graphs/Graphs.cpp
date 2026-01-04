#include <iostream>
#include <vector>

//Да се напише функция, която намира сумата на най - големите елементи на отделните свързани компоненти в (неориентиран) граф.

void findMaxEl(std::vector<std::vector<int>>& adj, int src, std::vector<bool>& visited, int& maxEl) {
	visited[src] = true;
	maxEl = std::max(maxEl, src);
	for (const auto& neigbour : adj[src]) {
		if (!visited[neigbour])
			findMaxEl(adj, neigbour, visited, maxEl);
	}
}

int getSum(std::vector<std::vector<int>>& adj) {
	int finalSum = 0;
	std::vector<bool> visited(adj.size(), false);
	for (int i = 0;i < adj.size();i++) {
		if (!visited[i]) {
			int currMax = INT_MIN;
			findMaxEl(adj, i, visited, currMax);
			finalSum += currMax;
		}
	}
	return finalSum;
}
