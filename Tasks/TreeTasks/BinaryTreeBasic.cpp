#include <iostream>

struct Node {
	int data;
	Node* left;
	Node* right;

	Node(int data):data(data),left(nullptr),right(nullptr){}
};

//count nodes
int countNodes(Node* root) {
	if (!root)
		return 0;

	if (!root->left || !root->right)
		return 1;

	return 1 + countNodes(root->left) + countNodes(root->right);
}

//sum nodes
int sumNodes(Node* root) {
	if (!root)
		return 0;
	return root->data + sumNodes(root->left) + sumNodes(root->right);
}

//find max el
int maxEl(Node* root) {
	if (!root)
		return 0;
	if (!root->left || root->right)
		return root->data;
	return std::max(root->data, std::max(maxEl(root->left), maxEl(root->right)));
}

//contains el
bool contains(Node* root,int val) {
	if (!root)
		return false;
	if (root->data == val)
		return true;
	return contains(root->left, val) || contains(root->right, val);
}

//is leaf
bool isLeaf(Node* node) {
	return node && !node->left && !node->right;
}

//get height
int getHeight(Node* root) {
	if (!root)
		return -1;
	return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

//delete tree
void deleteTree(Node* root) {
	if (!root)
		return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

int main() {

	Node* root = new Node(6);
	root->left = new Node(3);
	root->right = new Node(8);
	root->left->left = new Node(7);
	root->left->right = new Node(1);
	root->right->left = new Node(5);
	root->right->right = new Node(6);

	std::cout << maxEl(root) << std::endl;

	deleteTree(root);

}