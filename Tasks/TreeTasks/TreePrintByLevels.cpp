#include <iostream>
#include <queue>

struct Node {
	char data;
	std::vector<Node*> children;

	Node(char data):data(data){}
};

void printByLevels(Node* root) {
	std::queue<Node*> levels;
	levels.push(root);

	while (!levels.empty()) {
		int size = levels.size();
		for (int i = 0;i < size;i++) {
			Node* curr = levels.front();
			levels.pop();

			std::cout << curr->data << " ";

			if (!curr->children.empty()) {
				for (const auto& Node : curr->children)
					levels.push(Node);
			}
		}
		std::cout << std::endl;
	}
}