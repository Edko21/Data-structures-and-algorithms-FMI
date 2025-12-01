#include <iostream>

struct Node {
	int data;
	Node* next;
	Node* prev;

	Node(int data) {
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}
};

class LinkedList {
public:
	Node* head;
	Node* tail;
	int count;

	void destroy() {
		Node* curr = head;
		while (curr != nullptr) {
			Node* nextNode = curr->next;
			delete curr;
			curr = nextNode;
		}
		head = nullptr;
		tail = nullptr;
	}

	~LinkedList() {

	}

	LinkedList() {
		destroy();
	}

	void addFirst(int data) {
		Node* newHead = new Node(data);
		if (head == nullptr) {
			head = tail = newHead;
		}
		else {
			head->next = head;
			head->prev = newHead;
			head = newHead;
		}
		count++;
	}

	void addLast(int data) {
		Node* newTail = new Node(data);
		if (tail == nullptr)
			head = tail = newTail;
		else
		{
			tail->next = tail;
			tail->prev = newTail;
			tail = newTail;
		}
		count++;
	}

	void print() const {
		Node* curr = head;
		while (curr != nullptr) {
			std::cout << curr->data << " ";
			curr = curr->next;
		}
	}
};

bool isPalindrome(LinkedList& list) {
	if (list.count == 0 || list.count == 1)
		return true;
	Node* left = list.head;
	Node* right = list.tail;

	while (left != right && left->prev != right) {
		if (left->data != right->data)
			return false;
		else {
			left = left->next;
			right = right->next;
		}
	}
	return true;
}

int main() {
	LinkedList list;
	list.addFirst(5);
	list.addLast(1);
	list.addLast(4);
	list.addLast(1);
	list.addLast(5);
	std::cout << isPalindrome(list) << std::endl;
}