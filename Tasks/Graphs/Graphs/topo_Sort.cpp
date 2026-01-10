#include <iostream>
#include <vector>
#include <stack>


class Graph {
	std::vector<std::vector<int, int>> adj;
	bool oriented;
	void topoSort_Rec(size_t start, std::vector<bool>& visited, std::stack<size_t>& st) const;
	size_t v;

public:
	Graph(size_t vertexCount, bool isOriented);
	void addEdge(size_t start, size_t end, int weight);

	size_t shortestPath(size_t start, size_t end, std::vector<size_t>& path) const;

	std::vector<size_t> topo_sort() const;
};

void Graph::topoSort_Rec(size_t start, std::vector<bool>& visited, std::stack<size_t>& st) const {
	visited[start] = true;
	for (int i = 0;i < adj[start].size(); i++) {
		size_t neighbor = adj[start][i];
		if (!visited[neighbor])
			topoSort_Rec(neighbor, visited, st);
	}
	st.push(start);
}

std::vector<size_t> Graph::topo_sort() const {
	std::vector<bool> visited(v);
	std::stack<size_t> st;

	for (int i = 0;i < v;i++) {
		if (!visited[i])
			topoSort_Rec(i, visited, st);
	}
	std::vector<size_t> res(v);
	for (int i = 0;i < v;i++) {
		res[i] = st.top();
		st.pop();
	}
	return std::move(res);
}