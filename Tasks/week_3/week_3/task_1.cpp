#include <stack>
#include <iostream>

//reverse stack

void insertAtBottom(std::stack<int>& s, int x) {
	if (s.empty()) {
		s.push(x);
		return;
	}

	int top = s.top();
	s.pop();
	insertAtBottom(s, x);
	s.push(top);
}

void reverseStack(std::stack<int>& s) {
	if (s.empty())
		return;

	int top = s.top();
	s.pop();
	reverseStack(s);
	insertAtBottom(s, top);
}

int main() {
	std::stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);

	reverseStack(st);

	while (!st.empty()) {
		std::cout << st.top() << " ";
		st.pop();
	}
	return 0;
}