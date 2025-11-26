#ifndef _NODE_T_H_
#define _NODE_T_H_

#include <iostream>


template <typename T>
struct Node {
    T value;  
    Node<T>* next; 

    Node(T value = T(), Node* next = nullptr)
        : value(value), next(next)
    {
    }

    ~Node() {
        delete next;
    }

    void add(T value) {
        Node<T>* last = this;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = new Node<T>(value);
    }

    void print() const {
        const Node<T>* current = this;
        while (current->next != nullptr) {
            std::cout << current->value << " -> ";
            current = current->next;
        }
        std::cout << current->value << std::endl;
    }
};

#endif 
