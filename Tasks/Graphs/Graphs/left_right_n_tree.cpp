#include <queue>
#include <iostream>

struct Node {
	int val;
	std::vector<int> children;

	Node(int val):val(val){}
};

std::vector<int> leftLook(Node* root) {
	std::queue<Node*> currLevel;
	std::vector<int> leftView;

	leftView.push_back(root->val);
	currLevel.push(root);

	while (!currLevel.empty()) {
		auto currSize = currLevel.size();

		for (int i = 0;i < currSize;i++) {
			Node* currTop = currLevel.front();
			currLevel.pop();
			
			for (const auto& child : currTop->children) {
				if (child)
					currLevel.push(child);
			}

		}
		if (!currLevel.empty())
			leftView.push_back(currLevel.front()->val);

	}
	return leftView;
}

std::vector<int> rightLook(Node* root) {
	std::queue<Node*> currLevel;
	std::vector<int> rightView;

	rightView.push_back(root->val);
	currLevel.push(root);

	while (!currLevel.empty()) {
		auto currSize = currLevel.size();

		for (int i = 0;i < currSize;i++) {
			Node* currTop = currLevel.front();
			currLevel.pop();

			for (const auto& child : currTop->children) {
				if (child) {
					currLevel.push(child);
				}
			}
		}
		if (!currLevel.empty())
			rightView.push_back(currLevel.front()->val);
	}
	return rightView;
}

int main(int argc, const char* argv[]) {
	Node* root = new Node(6);
	root->children.push_back(new Node(8));
	root->children.push_back(new Node(5));
	root->children.push_back(new Node(4));
	root->children.at(0)->children.push_back(new Node(0));
	root->children.at(0)->children.push_back(new Node(1));
	root->children.at(1)->children.push_back(new Node(2));
	root->children.at(1)->children.push_back(new Node(3));
	root->children.at(1)->children.push_back(new Node(10));
	root->children.at(2)->children.push_back(new Node(11));
	root->children.at(2)->children.at(0)->children.push_back(new Node(16));

	auto left_view = rightLook(root);
	for (const auto& el : left_view)
		std::cout << el << " ";

}