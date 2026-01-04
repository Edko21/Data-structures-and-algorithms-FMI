#include<iostream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>


struct Node {
	int data;
	std::vector<Node*> children;

	Node(int data):data(data){}
};

struct Node_Char {
	char data;
	std::vector<Node_Char*> children;

	Node_Char(char data):data(data){}
};

void clear(Node* root) {
	if (!root)
		return;
	for (auto& child : root->children)
		clear(child);
	delete root;
}


void generateWords(Node_Char* root, std::string& temp, std::vector<std::string>& words) {
	if (!root)
		return;
	temp += root->data;
	if (root->children.empty()) {
		words.push_back(temp);
		temp.pop_back();
		return;
	}
	for (const auto& child : root->children)
		generateWords(child, temp, words);
	temp.pop_back();
}

std::vector<std::string> allWords(Node_Char* root) {
	std::string temp;
	std::vector<std::string> words;
	generateWords(root, temp, words);
	return words;
}


template <typename T>
struct NodeFull {
	T data;
	std::vector<NodeFull<T>*> children;

	NodeFull(T data):data(data){}
};

//Given random tree write function to check if it contains element
template <typename T>
bool containsEl(NodeFull<T>* root, T el) {
	if (!root)
		return false;
	int size = root->children.size();

	if (root->data == el)
		return true;

	for (int i = 0;i < size;i++) {
		if (containsEl(root->children[i], el))
			return true;
	}
	return false;
}

//Given random tree write function that sums all of the elements
template <typename T>
int sum(NodeFull<T>* root) {
	if (!root)
		return 0;
	int sum = root->data;

	for (int i = 0;i < root->children.size();i++) {
		sum += sum(root->children[i]);
	}
	return sum
}


//Given random tree write function that returns the max el
template <typename T>
T maxEl(NodeFull<T>* root) {
	T max_El = root->data;
	for (int i = 0;i < root->children.size();i++) {
		maxEl = std::max(maxEl, maxEl(root->children[i]);
	}
	return max_El;
}


//Given random tree write function that finds the height 
template <typename T>
int height(NodeFull<T>* root) {
	int maxHeight = -1;

	for (int i = 0;i < root->children.size();i++) {
		int currHeight = height(root->children[i]);
		if (currHeight > maxHeight) {
			maxHeight = currHeight;
		}
	}
	return maxHeight + 1;
}


//Given random tree write function that returns the number of el
template <typename T>
int getNumOfEl(NodeFull<T>* root) {
	int num = 1;
	for (int i = 0;i < root->children.size();i++) {
		num += getNumOfEl(root->children[i]);
	}
	return num;
}

template <typename T>
std::string word(NodeFull<T>* root, int k) {
	std::string wordOnLevel;

	if (root == nullptr)
		return "";
	if (k == 1)
		return wordOnLevel + (char)root->data;

	for (int i = 0;i < root->children.size();i++) {
		wordOnLevel += word(root->children[i], k - 1);
	}
	return wordOnLevel;
}


void fillWords(NodeFull<char>* root, std::vector<std::string>& v, std::string currWord) {
	currWord += root->data;

	if (root->children.size() == 0) {
		v.push_back(currWord);
		return;
	}

	for (int i = 0;i < root->children.size();i++) {
		fillWords(root->children[i], v, currWord);
	}
}

//