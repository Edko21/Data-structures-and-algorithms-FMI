#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>

class Graph {
	std::vector<std::vector<int>> adj;
	bool oriented;

public:
	Graph(size_t vertexCount, bool isOriented);
	void addEdge(size_t start, size_t end);

	void BFS(size_t start) const;
	void DFS_REC(size_t start) const;
	void dfs_helper(size_t curr, std::vector<bool>& visited, std::vector<size_t>& res) const;
	int BFS_shoretst_path(size_t start, size_t end) const;

	bool containsCycle() const;
};

Graph::Graph(size_t vertexCount, bool isOriented):adj(vertexCount),oriented(isOriented) {}

void Graph::addEdge(size_t start, size_t end) {
	adj[start].push_back((int)end);
	if (!oriented) {
		adj[end].push_back((int)start);
	}
}

void Graph::BFS(size_t start) const {
	std::vector<bool> visited(adj.size());

	std::queue<size_t> q;
	q.push(start);
	visited[start] = true;

	while (!q.empty()) {
		size_t currVertex = q.front();
		q.pop();

		for (int i = 0;i < adj[currVertex].size();i++) {
			size_t neighbor = adj[currVertex][i];
			if (visited[neighbor])
				continue;

			std::cout << neighbor;
			visited[neighbor] = true;
			q.push(neighbor);
		}
	}
}

int Graph::BFS_shoretst_path(size_t start, size_t end) const {
	if (start == end) return 0;

	std::vector<bool> visited(adj.size(), false);
	std::queue<size_t> q;

	q.push(start);
	visited[start] = true;

	int dist = 0;

	while (!q.empty()) {
		size_t currLevelSize = q.size();
		for (size_t i = 0;i < currLevelSize;i++) {
			size_t currVertex = q.front();
			q.pop();

			for (auto neigbor : adj[currVertex]) {
				if (visited[neigbor]) continue;
				if (neigbor == end)
					return dist + 1;

				q.push(neigbor);
				visited[neigbor] = true;
			}
		}
		dist++;
	}
	return -1;
}

void Graph::dfs_helper(size_t curr, std::vector<bool>& visited, std::vector<size_t>& res) const {
	visited[curr] = true;
	std::cout << curr << " ";
	for (auto neighbor : adj[curr]) {
		if (!visited[neighbor])
			dfs_helper(neighbor, visited, res);
	}
}

void Graph::DFS_REC(size_t start) const {
	std::vector<bool> visited(adj.size(), false);
	std::vector<size_t> res;

	dfs_helper(start, visited, res);
}