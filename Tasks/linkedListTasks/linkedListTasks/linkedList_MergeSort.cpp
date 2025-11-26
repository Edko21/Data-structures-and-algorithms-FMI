#include <iostream>

struct Node {
	int data = 0;
	Node* next = nullptr;

	Node(int data,Node* next=nullptr):data(data),next(next){}
};

void print(const Node* root) {
	while (root) {
		std::cout << root->data;
		if (root->next)
			std::cout << "->";
		root = root->next;
	}
	std::cout << std::endl;
}

void freeList(Node* root) {
	Node* curr = root;
	while (curr) {
		Node* next = curr->next;
		delete curr;
		curr = next;
	}
}

void pushBack(Node*& resBegin, Node*& resEnd, Node* toAdd) {
	if (!resBegin) {
		resBegin = resEnd = toAdd;
	}
	else {
		resEnd->next = toAdd;
		resEnd = toAdd;
	}
}

Node* mergeLists(Node* first, Node* second) {
	Node* resBegin = nullptr, * resEnd = nullptr;

	while (first && second) {
		if (first->data < second->data) {
			pushBack(resBegin, resEnd, first);
			first = first->next;
		}
		else {
			pushBack(resBegin, resEnd, second);
			second = second->next;
		}
	}

	if (!first) {
		pushBack(resBegin, resEnd, second);
	}
	else {
		pushBack(resBegin, resEnd, first);
	}
	return resBegin;
}

Node* getMid(Node* list) {
	if (!list)
		return nullptr;
	Node* slow = list;
	Node* fast = list->next;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

Node* mergeSort(Node* list) {
	if (!list || !list->next)
		return list;
	Node* mid = getMid(list);

	Node* left = list;
	Node* right = mid->next;
	mid->next = nullptr;

	left = mergeSort(left);
	right = mergeSort(right);

	return mergeLists(left, right);
}

int main()
{
	Node* list = new Node(20, new Node(14, new Node(7, new Node(3))));
	list = mergeSort(list);
	print(list);
	freeList(list);
}