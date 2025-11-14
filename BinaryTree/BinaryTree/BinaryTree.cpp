#pragma once
#include <iostream>

struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int data) :data(data), left(nullptr), right(nullptr) {}
};

int countNodes(TreeNode* root) {
	if (!root)
		return 0;
	if (!root->left && !root->right)
		return 1;
	return 1 + countNodes(root->left) + countNodes(root->right);
}

int sumNodes(TreeNode* root) {
	if (!root)
		return 0;
	return root->data + sumNodes(root->left) + sumNodes(root->right);
}

int maxEl(TreeNode* root) {
	if (!root)
		throw std::runtime_error("invalid");
	if (!root->left && !root->right)
		return root->data;
	return std::max(root->data, std::max(maxEl(root->left), maxEl(root->right)));
}

bool containsEl(TreeNode* root, int val) {
	if (!root)
		return false;
	if (root->data == val)
		return true;
	return containsEl(root->left, val) || containsEl(root->right, val);
}

bool isLeaf(TreeNode* node) {
	return node && !node->left && !node->right;
}

int getHight(TreeNode* root) {
	if (!root)
		return -1;
	return 1 + std::max(getHight(root->left), getHight(root->right));
}

void deleteTree(TreeNode* root) {
	if (!root)
		return;
	deleteTree(root->left);
	deleteTree(root->right);

	delete root;
}

int main() {

	TreeNode* root = new TreeNode(6);
	root->left = new TreeNode(3);
	root->right = new TreeNode(8);
	root->left->left = new TreeNode(7);
	root->left->right = new TreeNode(1);
	root->right->left = new TreeNode(5);
	root->right->right = new TreeNode(6);

	std::cout << maxEl(root) << std::endl;

	deleteTree(root);

}