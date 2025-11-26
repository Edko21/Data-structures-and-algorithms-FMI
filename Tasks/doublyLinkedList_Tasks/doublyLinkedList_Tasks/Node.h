#pragma once
#include <iostream>

template <typename T>
class Node {
	T val;
	Node* prev;
	Node* next;

	Node(T val=T(),Node* prev=nullptr,Node* next=nullptr):val(val),next(next),prev(prev){}

	~Node() {
		if (prev != nullptr) {
			prev->next = nullptr;
			delete prev;
		}

		if (next != nullptr) {
			next->prev = nullptr;
			delete next;
		}
	}

	void addAtEnd(T val) {
		Node* last = this;
		while (last->next != nullptr) {
			last = last->next;
		}
		last->next = new Node(val, last);
	}

	void remove() {
		if (prev) {
			prev->next = next;
		}
		if (next) {
			next->prev = prev;
		}
		prev = nullptr;
		next = nullptr;
		delete this;
	}

	void printFromStart() const {
		const Node* current = this;
		while (current->prev != nullptr) {
			current = current->prev;
		}

		while (current->next != nullptr) {
			std::cout << current->value << " <-> ";
			current = current->next;
		}
		std::cout << current->value << std::endl;
	}
};
