#include <iostream>

struct Node {
	int data;
	Node* next;

	Node(int data,Node* next= nullptr):data(data),next(next){}
};

void free(Node* list) {
	while (list) {
		Node* toDel = list;
		list = list->next;
		delete toDel;
	}
}

void print(const Node* list) {
	while (list) {
		std::cout << list->data;
		if (list->next)
			std::cout<<"->";
		list = list->next;
	}
	std::cout << std::endl;
}

Node* reverse(Node* list) {
	if (list == nullptr || list->next == nullptr)
		return list;
	Node* curr = list;
	Node* prev = nullptr;

	while (curr != nullptr) {
		Node* temp = curr->next;
		curr->next = prev;
		prev = curr;
		curr = temp;
	}
	return prev;
}

Node* revRec(Node* list) {
	if (!list || !list->next)
		return list;
	Node* next = list->next;
	list->next = nullptr;

	Node* revFromNext = revRec(next);

	next->next = list;
	return revFromNext;
}

int main()
{
	Node* list = new Node(20, new Node(14, new Node(7)));

	list = reverse(list);
	print(list);

	list = revRec(list);

	print(list);

	free(list);
}


