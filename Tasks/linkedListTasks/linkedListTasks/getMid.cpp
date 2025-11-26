#include <iostream>

struct Node {
	int data = 0;
	Node* next;

	Node(int data,Node* next=nullptr):data(data),next(next){}
};

void print(Node* list) {
	while (list) {
		Node* toDel = list->next;
		list = list->next;
		delete toDel;
	}
}

void freeList(Node* root) {
	Node* curr;
	while (curr) {
		Node* next = curr->next;
		delete curr;
		curr = next;
	}
}

const Node* getMid(const Node* head) {
	const Node* slow = head;
	const Node* fast = head->next;
	
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

int main()
{
	Node* list = new Node(20, new Node(14, new Node(7)));

	std::cout << getMid(list)->data << std::endl;

	free(list);

}