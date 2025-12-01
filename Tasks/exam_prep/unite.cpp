#include <iostream>
// A singly linked *cyclic* list is given, whose elements are strings.
// Implement a function unite(Node* list), which receives as a parameter a pointer
// to an element of the cyclic list of strings, and merges all pairs of consecutive
// elements for which the last character of one element matches the first character
// of the next element. They must be merged into a single element whose string is
// formed by concatenating the two strings separated by a hyphen.
//
// The function must print the list to the standard output, starting from the
// lexicographically smallest string.

struct Node {
	std::string data;
	Node* next;
	Node(const std::string& data):data(data),next(nullptr){}
};

void print(Node* list) {
	Node* iter = list;
	do {
		std::cout << iter->next << std::endl;
		iter = iter->next;
	} while (iter != list);
}

bool shouldUnite(const std::string& lhs, const std::string& rhs) {
	if (lhs == "" || rhs == "")
		return false;
	return lhs[lhs.size() - 1] == rhs[0];
}

void absorb(Node* first, Node* second) {
	first->data.append("->");
	first->data.append(second->data);

	first->next = second->next;
	delete second;
}

void unite(Node* list) {
	Node* first = list;
	Node* second = first;

	bool shouldFinish = false;
	do
	{
		if (list->next == first)
			shouldFinish = true;

		if (shouldUnite(list->data, list->next->data))
			absorb(list, list->next);
		else
		{
			list = list->next;

			if (list->data < lexMin->data)
				lexMin = list;
		}
	} while (!shouldFinish);

	print(lexMin);
	free(lexMin);
}

int main()
{
	Node* f1 = new Node("street");
	Node* f2 = new Node("taxi");
	Node* f3 = new Node("ink");
	Node* f4 = new Node("dog");
	Node* f5 = new Node("smile");
	Node* f6 = new Node("eat");
	Node* f7 = new Node("tall");
	Node* f8 = new Node("pass");

	f1->next = f2;
	f2->next = f3;
	f3->next = f4;
	f4->next = f5;
	f5->next = f6;
	f6->next = f7;
	f7->next = f8;
	f8->next = f1;

	unite(f6);
}