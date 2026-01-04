#include <iostream>
#include <vector>
#include <queue>
#include <stack>


class Graph {
	std::vector<std::vector<std::pair<int, int>>> adj;
	bool oriented;

public:
	Graph(size_t vertexCount, bool isOriented);
	void addEdge(size_t start, size_t end, int weight);

	size_t shortestPath(size_t start, size_t end, std::vector<size_t>& path) const;
};

Graph::Graph(size_t vertexCount,bool isOriented): adj(vertexCount),oriented(isOriented){}

void Graph::addEdge(size_t start, size_t end, int weight) {
	adj[start].push_back({ end,weight });

	if (!oriented) {
		adj[end].push_back({ start,weight });
	}
}

size_t Graph::shortestPath(size_t start, size_t end, std::vector<size_t>& path) const {
	struct VertexAndDist {
		size_t currVertex;
		size_t dist;
		
		bool operator<(VertexAndDist& other) const {
			return dist > other.dist;
		}
	};

	std::vector<size_t> distances(adj.size(), INT_MAX);
	std::vector<size_t> prev(adj.size(), INT_MAX);
	std::vector<bool> found(adj.size(), false);

	distances[start] = 0;
	std::priority_queue<VertexAndDist> pq;

	pq.push({ start,0 });

	while (!pq.empty()) {
		auto currClosest = pq.top();
		pq.pop();

		if (found[currClosest.currVertex])
			continue;
		found[currClosest.currVertex] = true;

		if (end == currClosest.currVertex) {
			while (end != start) {
				path.push_back(end);
				end = prev[end];
			}
			path.push_back(start);

			std::reverse(path.begin(), path.end());

			return currClosest.dist;
		}
		for (auto& edge : adj[currClosest.currVertex]) {
			size_t n = edge.first;
			size_t edgeWeight = edge.second;

			if (distances[n] > distances[currClosest.currVertex] + edgeWeight) {
				distances[n] = distances[currClosest.currVertex] + edgeWeight;
				pq.push({ n,distances[currClosest.currVertex] + edgeWeight });
				prev[n] = currClosest.currVertex;
			}
		}
	}
	return 0;
}

int main()
{
	Graph g(3, true);
	g.addEdge(0, 1, 3);
	g.addEdge(0, 2, 10);
	g.addEdge(1, 2, 4);

	std::vector<size_t> path;
	std::cout << g.shortestPath(0, 2, path) << std::endl;

	for (int i = 0; i < path.size(); i++)
		std::cout << path[i] << " ";
	return 0;
}