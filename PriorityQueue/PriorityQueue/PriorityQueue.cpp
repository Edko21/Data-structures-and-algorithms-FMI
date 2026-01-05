 #pragma once
#include <iostream>
#include <vector>

template <typename T>
class PriorityQueue
{
    static size_t leftChild(size_t i);
    static size_t rightChild(size_t i);
    static int parent(int i);

    void heapify(size_t ind);
    std::vector<T> data;

public:
    PriorityQueue() = default;
    PriorityQueue(const std::vector<T>& v);

    bool isEmpty() const;
    const T& peek() const;
    void pop(); 
    void insert(const T& el);
    size_t size() const;
};

template <typename T>
int PriorityQueue<T>::parent(int i) {
    return (i - 1) / 2;
}

template <typename T>
size_t PriorityQueue<T>::leftChild(size_t i) {
	return 2 * i + 1;
}

template <typename T>
size_t PriorityQueue<T>::rightChild(size_t i) {
	return 2 * i + 2;
}

template <typename T>
void PriorityQueue<T>::heapify(size_t ind) {
	int currElInd = ind;
	while (true) {
		int leftChildInd = leftChild(currElInd);
		int rightChildInd = rightChild(currElInd);

        bool shouldGoLeft = leftChildInd<data.size() && data[leftChildInd]>data[currElInd];
        bool shouldGoRight = rightChildInd<data.size() && data[rightChildInd]>data[currElInd];

        if (shouldGoLeft && shouldGoRight) {
            if (data[leftChildInd] > data[rightChildInd]) {
                std::swap(data[currElInd], data[leftChildInd]);
                currElInd = leftChildInd;
            }
            else {
                std::swap(data[currElInd], data[rightChildInd]);
                currElInd = rightChildInd;
            }
        }
        else if (shouldGoLeft) {
            std::swap(data[currElInd], data[leftChildInd]);
            currElInd = leftChildInd;
        }
        else if (shouldGoRight) {
            std::swap(data[currElInd], data[rightChildInd]);
            currElInd = rightChildInd;
        }
        else
            break;
	}
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const {
    return data.empty();
}

template <typename T>
const T& PriorityQueue<T>::peek() const {
    if (isEmpty())
        throw std::runtime_error("empty queue");
    return data[0];
}

template <typename T>
void PriorityQueue<T>::pop() {
    if (isEmpty())
        throw std::runtime_error("empty queue");
    data[0] = data[data.size() - 1];
    data.pop_back();

    if (data.size() != 0) {
        heapify(0);
    }
}
template <typename T>
void PriorityQueue<T>::insert(const T& el){
    data.push_back(el);
    int ind = data.size() - 1;
    int parentIndex = parent(ind);

    while (ind > 0 && data[ind] > data[parentIndex])
    {
        std::swap(data[ind], data[parentIndex]);
        ind = parentIndex;
        parentIndex = parent(ind);
    }
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const std::vector<T>& v)  {
    data = v;

    for (int i = v.size() / 2 - 1; i >= 0; i--)
        heapify(i);
}

template <typename T>
size_t PriorityQueue<T>::size() const{
    return data.size();
}