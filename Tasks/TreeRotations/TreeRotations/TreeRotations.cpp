#include <iostream>

struct Node {
	int data;
	Node* left;
	Node* right;	

	Node(int data):data(data),left(nullptr),right(nullptr){}
};

void clear(Node* root) {
	if (!root)
		return;
	clear(root->left);
	clear(root->right);
	delete root;
}

Node* leftRotation(Node* root) {
	if (!root || !root->right)
		return root;

	Node* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;
	root = newRoot;
	return root;
}

Node* rightRotation(Node* root) {
	if (!root || !root->left)
		return root;

	Node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	root = newRoot;
	return root;
}

Node* leftRightRotation(Node* root) {
	if (!root || !root->right)
		return root;
	root->left = leftRotation(root->left);
	return rightRotation(root);
}

Node* rightLeftRotation(Node* root) {
	if (!root || !root->left)
		return root;
	root->right = rightRotation(root->right);
	return leftRotation(root);
}

int main(int argc, const char* argv[]) {
	Node* root = new Node(1);
	root->right = new Node(2);
	root->right->right = new Node(3);

	root = leftRotation(root);
	std::cout << root->data << " " << root->left->data << " " << root->right->data << std::endl;

	root = rightRotation(root);
	std::cout << root->data << " " << root->right->data << " " << root->right->right->data << std::endl;


	Node* root2 = new Node(5);
	root2->left = new Node(3);
	root2->left->right = new Node(4);
	root2 = leftRightRotation(root2);
	std::cout << root2->data << " " << root2->left->data << " " << root2->right->data << std::endl;

	Node* root3 = new Node(3);
	root3->right = new Node(5);
	root3->right->left = new Node(4);
	root3 = rightLeftRotation(root3);
	std::cout << root3->data << " " << root3->left->data << " " << root3->right->data << std::endl;

	clear(root);
	clear(root2);
	clear(root3);

