#include <iostream>
#include <string>

char* readCString(std::istream& is) {
	int len = 0;
	is >> len;
	if (len < 0)
		return nullptr;

	try {
		char* res = new char[len + 1];
		is.get();
		is.read(res,len);

		if (!is) {
			delete[] res;
			return nullptr;
		}
		res[len] = '\0';
		return res;
	}
	catch (std::bad_alloc&) {
		return nullptr;
	}
}

void print(const char* const cstr) {
	if (cstr != nullptr) 
		std::cout << cstr << '\n';
	else
		std::cout << "nullptr\n";
}
