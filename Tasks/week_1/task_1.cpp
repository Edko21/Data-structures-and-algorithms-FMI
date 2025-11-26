#include <iostream>

template <class T>
void swap(T* lhs, T* rhs) { //with poiter
	T temp = *lhs;
	*lhs = *rhs;
	*rhs = temp;
}

template <class T>
void swap(T& lhs, T& rhs) { //with refrence 
	T temp = lhs;
	lhs = rhs;
	rhs = temp;
}

