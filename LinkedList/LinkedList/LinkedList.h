#pragma once
#include <iostream>

template <typename T>
class LinkedList {
private:
	struct Node {
		T data;
		Node* next;

		Node(const T& data) {
			this->data = data;
			next = nullptr;
		}
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

	void copyFrom(const LinkedList<T>& other);
	void moveFrom(LinkedList<T>&& other);
	void free();

public:
	LinkedList() = default;
	LinkedList(const LinkedList<T>& other);
	LinkedList<T>& operator=(const LinkedList<T>& other);
	~LinkedList();

	LinkedList(LinkedList<T>&& other);
	LinkedList<T>& operator=(LinkedList<T>&& other);

	void pushFront(const T& el);
	void pushBack(const T& el);
	void popFront();

	const T& front() const;
	const T& back() const;

	T& front();
	T& back();

	size_t getSize() const;
	bool isEmpty() const;

	template<typename U>
	friend LinkedList<U> concat(LinkedList<U>& lhs, LinkedList<U>& rhs);

	void print() const;

	class Iter {
	private:
		Node* currElPtr;
		friend class LinkedList;
	public:
		Iter(Node* currElPtr = nullptr):currElPtr(currElPtr){}

		T& operator*() {
			return currElPtr->data;
		}

		T* operator->() {
			return &currElPtr->data;
		}

		Iter& operator++() {
			if (currElPtr)
				currElPtr = currElPtr->next;
			return *this;
		}

		Iter operator++(int) {
			Iter copy(*this);
			++(*this);
			return copy;
		}

		Iter& operator+=(size_t s) {
			while (s--)
				++(*this);
			return *this;
		}

		Iter operator+(int i)const {
			Iter res(*this);
			return res += i;
		}

		bool operator==(const Iter& rhs) const {
			return (currElPtr == rhs.currElPtr);
		}

		bool operator!=(const Iter& rhs) const {
			return !(currElPtr == *this);
		}
	};

	class constIter {
	private:
		Node* currElPtr;
		friend class LinkedList;

	public:
		constIter(Node* currElPtr=nullptr):currElPtr(currElPtr){}

		const T& operator*() const {
			return currElPtr->data;
		}

		const T* operator->() const {
			return &currElPtr->data;
		}

		constIter& operator++() {
			if (currElPtr)
				currElPtr = currElPtr->next;
			return *this;
		}

		constIter operator++(int) {
			constIter copy(*this);
			++(*this);
			return copy;
		}

		constIter& operator+=(size_t s) {
			while (s--)
				++(*this);
			return *this;
		}

		constIter operator+(int i)const {
			constIter res(*this);
			return res += i;
		}

		bool operator==(const constIter& rhs) const {
			return (currElPtr == rhs.currElPtr);
		}

		bool operator!=(const constIter& rhs) const {
			return !(currElPtr == *this);
		}
	};

	Iter begin() {
		return Iter(head);
	}

	Iter end() {
		return Iter(nullptr);
	}

	constIter cbegin() const{
		return constIter(head);
	}

	constIter cend() const {
		return constIter(nullptr);
	}

	Iter insertAfter(const T& el, const constIter& it);
	Iter removeAfter(const constIter& it);
};	

template<typename T>
void LinkedList<T>::pushFront(const T& el) {
	Node* newNode = new Node(el);

	if (isEmpty()) {
		head = tail = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}
	size++;	
}

template<typename T>
void LinkedList<T>::pushBack(const T& el) {
	Node* newNode = new Node(el);

	if (isEmpty()) {
		head = tail = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}
	size++;
}

template<typename T>
void LinkedList<T>::popFront() {
	if (!head)
		throw std::runtime_error("empty list");
	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		Node* toDelete = head;
		head = head->next;
		delete toDelete;
	}
	size--;
}

template<typename T>
const T& LinkedList<T>::front() const {
	if (!head)
		throw std::runtime_error("empty list");
	return head->data;
}

template<typename T>
const T& LinkedList<T>::back() const {
	if (!tail)
		throw std::runtime_error("empty list");
	return tail->data;
}

template<typename T>
T& LinkedList<T>::front() {
	if (!head)
		throw std::runtime_error("empty list");
	return head->data;
}

template<typename T>
T& LinkedList<T>::back() {
	if (!tail)
		throw std::runtime_error("empty list");
	return tail->data;
}

template<typename T>
size_t LinkedList<T>::getSize() const {
	return size;
}

template<typename T>
bool LinkedList<T>::isEmpty() const {
	return getSize() == 0;
}

template<typename T>
LinkedList<T> concat(LinkedList<T>& lhs, LinkedList<T>& rhs) {
	LinkedList<T> res;

	if (!lhs.head) {
		res.head = rhs.head;
		res.tail = rhs.tail;
	}
	else if(!rhs.head){
		res.head = lhs.head;
		res.tail = lhs.tail;
	}

	res.getSize = lhs.size() + rhs.size();
	rhs.size() = lhs.size() = 0;
	rhs.head = lhs.head = nullptr;

	return res;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {
	copyFrom(other);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {
	moveFrom(std::move(other));
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}


template<typename T>
LinkedList<T>::~LinkedList() {
	free();
}

template<typename T>
void LinkedList<T>::copyFrom(const LinkedList<T>& other) {
	Node* iter = other.head;
	while (iter) {
		pushBack(iter->data);
		iter = iter->next;
	}
}

template<typename T>
void LinkedList<T>::moveFrom(LinkedList<T>&& other) {
	head = other.head;
	tail = other.tail;
	size = other.size;

	other.head = other.tail = nullptr;
	other.size = 0;
}

template<typename T>
void LinkedList<T>::free() {
	Node* iter = head;
	while (iter) {
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
	head = tail = nullptr;
	size = 0;
}

template<typename T>
void LinkedList<T>::print() const {
	Node* iter = head;
	while (iter) {
		std::cout << iter->data << ' ';
		if (iter->next)
			std::cout << "->" << ' ';

		iter = iter->next;
	}
	std::cout << std::endl;
}

template<typename T>
typename LinkedList<T>::Iter
LinkedList<T>::insertAfter(const T& el, const typename LinkedList<T>::constIter& it) {
	if (it.currElPtr == nullptr)
		return end();

	Node* newNode = new Node(el);

	newNode->next = it.currElPtr->next;
	it.currElPtr->next = newNode;

	if (tail == it.currElPtr)
		tail = newNode;

	++size;
	return Iter(newNode);
}

template<typename T>
typename LinkedList<T>::Iter
LinkedList<T>::removeAfter(const typename LinkedList<T>::constIter& it) {
	if (it.currElPtr == nullptr || it.currElPtr->next == nullptr)
		return end();

	Node* nextNext = it.currElPtr->next->next;

	if (it.currElPtr->next == tail)
		tail = it.currElPtr;

	delete it.currElPtr->next;
	it.currElPtr->next = nextNext; 

	--size;
	return Iter(nextNext);
}

