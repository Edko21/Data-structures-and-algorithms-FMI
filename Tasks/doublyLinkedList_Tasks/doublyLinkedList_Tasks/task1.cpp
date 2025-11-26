#include "Node.h"
#include <iostream>

template <typename T>
void removeConsecutiveDuplicates(Node<T>* list) {
	if (list == nullptr)
		return;
	Node<T>* curr = list;
	while (curr->prev != nullptr) {
		curr = curr->prev;
	}
	while (curr->next != nullptr) {
		if (curr->val == curr->next->val) {
			curr->next->remove();
		}
		else {
			curr = curr->next;
		}
	}
}               