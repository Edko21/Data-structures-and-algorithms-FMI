#include "Node.h"
#include <iostream>

template <typename T>
void mirror(Node<T>* list) {
	if (list == nullptr)
		return;

	Node<T>* curr = list;
	while (curr->next != nullptr) {
		curr = curr->next;
	}

	Node<T>* tail = curr;
	do {
		tail->next = new Node<T>(curr->val, tail);
		tail = tail->next;
		curr = curr->prev;
	} while (curr != nullptr);
}

int main() {
	Node<int> l(1);
	l.addAtEnd(4);
	l.addAtEnd(5);
	l.printFromStart();

	mirror(&l);
	l.printFromStart();

	return 0;
}
