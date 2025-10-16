#pragma once
#include <iostream>
#include <unordered_map>

template<class T>
class DebugCountAlloc {
public:
	T* alloc() {
		T* memory = new T;
		assert(allocs.count(memory) == 0);
		allocs.insert({ memory,1 });
		++total_allocs;
		++total_mem;

		return memory;
	}
	
	void free(T* memory){
		if (checkPth(memory)) {
			size_t blockCnt = allocs[memory];
			if (blockCnt != 1)
				std::cerr << "Allocated as array";
			allocs.erase(memory);
			++total_frees;
			delete memory;
		}
	}

	T* allocArr(size_t count) {
		if (!count)
			std::cerr << "allocation of zero sized blocks";
		T* memory = new T[count];
		assert(allocs.count(memory) == 0);
		allocs.insert({ memory,count });
		++total_allocs;
		total_mem += count;

		return memory;
	}

	void freeArr(T* memory) {
		if (checkPth(memory)) {
			size_t blockCnt = allocs[memory];
			allocs.erase(memory);
			++total_frees;
			delete[] memory;
		}
	}

	void printStatistics(std::ostream& stream = std::cout)
	{
		stream
			<< "#### Debug counting Allocator ####\n"
			<< "Total allocations:      " << total_allocs << "\n"
			<< "Total deallocations:    " << total_frees << "\n"
			<< "Total memory leaks:     " << total_allocs - total_frees << "\n"
			<< "Total memory allocated: " << (total_mem * sizeof(T)) << "\n";

		if (!allocs.empty()) {
			stream << "Memory still in use:\n";
			for (const auto& alloc : allocs) {
				stream << "Address: " << alloc.first
					<< " " << sizeof(T) * alloc.second << " bytes\n";
			}
		}
	}

	void swap(DebugCountAlloc<T>& other) {
		std::swap(total_allocs, other.total_allocs);
		std::swap(total_mem, other.total_mem);
		std::swap(total_frees, other.total_frees);
		allocs.swap(other.allocs);
	}

private:
	bool checkPth(T* memory) {
		if (!memory) {
			std::cerr << "Dealocating nullptr\n";
			return false;
		}

		if (!allocs.count(memory)) {
			throw"Pointer not allocated";
		}
		return true;
	}

	std::unordered_map<const void*, size_t>allocs;
	size_t total_allocs = 0;
	size_t total_mem = 0;
	size_t total_frees = 0;
};


template <class T>
class DefaultAlloc {
public:
	T* alloc() {
		++total_allocs;
		return new T;
	}

	void free(T* mem) {
		if (mem)
			++total_frees;
		delete mem;
	}

	T* allocArr(size_t count) {
		++total_allocs;
		return new T[count];
	}

	void freeArr(T* mem) {
		if (mem)
			++total_frees;
		delete[] mem;
	}

	void printStatistics(std::ostream& stream = std::cout) {
		stream
			<< "#### Default Allocator ####\n"
			<< "Total allocations:   " << total_allocs << "\n"
			<< "Total deallocations: " << total_frees << "\n"
			<< "Total memory leaks:  " << total_allocs - total_frees << "\n";
	}

	void swap(DefaultAlloc<T>& other) {
		std::swap(total_allocs, other.total_allocs);
		std::swap(total_frees, other.total_frees);
	}

private:
	size_t total_allocs = 0;
	size_t total_frees = 0;
};