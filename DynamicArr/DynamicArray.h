#pragma once
#include <stdexcept>
#include <cassert>
#include "Allocator.hpp"

template <class DataType,class Allocator=DefaultAlloc<DataType>>
class DynArray {
private:
	DataType* data = nullptr;
	size_t size = 0;
	size_t cap = 0;
	Allocator alloc;

	void ensureSize(size_t newSize);
	void resize(size_t newCap);

public:
	explicit DynArray(unsigned initialCap = 16);
	DynArray(const DynArray& other);
	DynArray& operator=(const DynArray& other);

	template<class OtherType,class __>
	DynArray(const DynArray<OtherType, __>& other);

	template<class OtherType, class __>
	DynArray& operator=(const DynArray<OtherType,__>& other);

	~DynArray();

	DynArray(DynArray&& other);
	DynArray& operator=(DynArray&& other);

	void append(const DataType& el);
	void remove(size_t index);
	void clear();

	bool contains(const DataType& el) const;
	size_t getSize() const;
	size_t getCap() const;
	bool isEmpty() const;

	DataType get(size_t index) const;
	const DataType& operator[](size_t index) const;
	DataType& operator[](size_t index);

	template<class OtherType, class __>
	DynArray& operator+=(const DynArray<OtherType, __>& other);
	DynArray& operator+=(const DataType& el);

	class DArrayIterator {
		friend class DynArray;
	private:
		explicit DArrayIterator(DataType* pointer) :pointer(pointer);
		DataType* pointer;

	public:
		const DataType& operator*() const {
			return *pointer;
		}

		DataType& operstor* () {
			return *pointer;
		}

		DArrayIterator& operator++() {
			++pointer;
			return *this;
		}

		DArrayIterator& operator++(int) {
			DArrayIterator res(*this);
			++(*this);
			return res;
		}

		bool operator!=(const DArrayIterator& other) const {
			return pointer != other.pointer;
		}
	};

	DArrayIterator begin() {
		return DArrayIterator(data);
	}

	DArrayIterator end() {
		return DArrayIterator(data + size);
	}
};

template<class DataType,class Allocator>
DynArray<DataType, Allocator>::DynArray(unsigned initialCap) :data(nullptr), size(0), cap(initialCap) {
	if (initialCap == 0)
		throw std::invalid_argument("illegal initial size");
	data = alloc.allocArr(cap);
}

template<class DataType, class Allocator>
DynArray<DataType, Allocator>::~DynArray() {
	clear();
}

template<class DataType, class Allocator>
DynArray<DataType, Allocator>::DynArray(const DynArray& other) :data(nullptr), size(other.size), cap(other.cap) {
	cap = cap ? cap : 1;
	data = alloc.allocArr(cap);

	for (size_t i = 0;i < size;i++)
		data[i] = other[i];
}

template<class DataType, class Allocator>
DynArray<DataType, Allocator>::DynArray(DynArray&& other) :data(nullptr), size(other.size), cap(other.cap) {
	std::swap(data, other.data);
	alloc.swap(other.alloc);
}

template<class DataType, class Allocator>
DynArray<DataType, Allocator>& DynArray<DataType, Allocator>::operator=(const DynArray& other) {
	if (this != &other) {
		if (cap < other.size) {
			clear();
			ensureSize(other.cap);
		}
		for (size = 0;size < other.size;++size)
			data[size] = other[size];
	}
	return *this;
}

template<class DataType, class Allocator>
DynArray<DataType, Allocator>& DynArray<DataType, Allocator>::operator=(DynArray&& other) {
	if (this != &other) {
		std::swap(data, other.data);
		std::swap(size, other.size);
		std::swap(cap, other.cap);
		alloc.swap(other.alloc);
	}
	return *this;
}

template<class DataType, class Allocator>
template<class OtherType,class __>
DynArray<DataType, Allocator>::DynArray(const DynArray<OtherType, __>& other) :data(nullptr), size(other.getSize()), cap(other.getCap()) {
	data = alloc.allocArr(cap);
	for (size_t i = 0;i < size;++i)
		data[i] = other[i];
}

template <class DataType, class Allocator>
template <class OtherType, class __>
DynArray<DataType, Allocator>& DynArray<DataType, Allocator>::operator=(const DynArray<OtherType, __>& other)
{
	size = other.getSize();
	if (capacity < other.getSize()) {
		clear();
		ensureSize(other.getSize());
	}
	for (size = 0; size < other.getSize(); ++size)
		data[size] = other[size];
	return *this;
}

template <class DataType, class Allocator>
void DynArray<DataType, Allocator>::append(const DataType& elem)
{
	ensureSize(size + 1);
	data[size++] = elem;
}

template <class DataType, class Allocator>
void DynArray<DataType, Allocator>::remove(size_t index)
{
	if (index >= size)
		throw std::invalid_argument("Illegal index");
	for (size_t i = index; i < size - 1; ++i)
		data[i] = std::move(data[i + 1]);
	--size;
}

template <class DataType, class Allocator>
void DynArray<DataType, Allocator>::clear()
{
	allocator.freeArr(data);
	data = nullptr;
	size = 0;
	capacity = 0;
}

template <class DataType, class Allocator>
bool DynArray<DataType, Allocator>::contains(const DataType& elem) const
{
	for (size_t i = 0; i < size; ++i)
		if (elem == data[i])
			return true;
	return false;
}

template <class DataType, class Allocator>
size_t DynArray<DataType, Allocator>::getSize() const { 
	return size;
}

template <class DataType, class Allocator>
size_t DynArray<DataType, Allocator>::getCap() const { 
	return capacity; 
}

template <class DataType, class Allocator>
bool DynArray<DataType, Allocator>::isEmpty() const { 
	return size == 0; 
}

template <class DataType, class Allocator>
DataType DynArray<DataType, Allocator>::get(size_t index) const
{
	if (index < size) 
		return data[index];
	return DataType();
}

template <class DataType, class Allocator>
const DataType& DynArray<DataType, Allocator>::operator[](size_t index) const
{
	if (index < size) 
		return data[index];
	throw std::invalid_argument("Illegal index");
}

template <class DataType, class Allocator>
DataType& DynArray<DataType, Allocator>::operator[](size_t index)
{
	if (index < size) 
		return data[index];
	throw std::invalid_argument("Illegal index");
}

template <class DataType, class Allocator>
void DynArray<DataType, Allocator>::ensureSize(size_t newSize)
{
	size_t newCap = data ? capacity : 1;
	while (newCap < newSize) 
		newCap *= 2;
	if (newCap != capacity) 
		resize(newCap);
}

template <class DataType, class Allocator>
void DynArray<DataType, Allocator>::resize(size_t newCapacity)
{
	DataType* newData = allocator.allocArr(newCapacity);
	for (size_t i = 0; i < size && i < newCapacity; ++i)
		newData[i] = data[i];
	allocator.freeArr(data);
	data = newData;
	capacity = newCapacity;
	if (size > capacity) 
		size = capacity;
}