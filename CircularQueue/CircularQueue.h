#include <iostream>

namespace SIZE {
	const size_t DEFAULT_CAP = 4;
}

template<typename T>
class Queue {
public:
	Queue();
	Queue(const Queue<T>& other);
	Queue<T>& operator=(const Queue<T>& other);
	~Queue();

	bool isEmpty() const;
	void enqueue(const T& el);
	void dequeue();
	const T& peek() const;

private:
	T* data;
	size_t cap;
	size_t count;

	size_t putIter;
	size_t getIter;

	void resize();
	void copyFrom(const Queue<T>& other);
	void free();
};

template<typename T>
Queue<T>::Queue() {
	data = new T[SIZE::DEFAULT_CAP];
	cap = SIZE::DEFAULT_CAP;
	count = 0;
	putIter = 0;
	getIter = 0;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other) {
	copyFrom(other);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Queue<T>::~Queue() {
	free();
}

template<typename T>
bool Queue<T>::isEmpty() const {
	return count == 0;
}

template<typename T>
void Queue<T>::enqueue(const T& el){
	if (count == cap)
		resize();
	data[putIter] = el;
	(++putIter) %= cap;
	count++;
}

template<typename T>
void Queue<T>::dequeue(){
	if (count == 0)
		throw std::runtime_error("empty queue");
	count--;
	(++getIter) %= cap;
}

template<typename T>
const T& Queue<T>::peek() const{
	if (count == 0)
		throw std::runtime_error("empty queue");
	return data[getIter];
}

template<typename T>
void Queue<T>::resize() {
	size_t newCap = cap * 2;
	size_t currCap = cap;

	T* temp = new T[newCap];
	for (int i = 0;i < currCap;++i) { 
		temp[i] = peek();
		dequeue();
	}

	getIter = 0;
	putIter = cap;
	count = cap;
	cap *= 2;

	delete[] data;
	data = temp;
}

template<typename T>
void Queue<T>::copyFrom(const Queue<T>& other) {
	data = new T[other.cap];
	for (int i = other.getIter;i != other.putIter;(i += 1) %= other.cap)
		data[i] = other.data[i];
	count = other.count;
	cap = other.cap;

	putIter = other.putIter;
	getIter = other.getIter;
}


template<typename T>
void Queue<T>::free() {
	delete[] data;
	data = nullptr;
	count = cap = 0;
}