#include <iostream>
#include <stack>

bool isOpening(char ch) {
	return ch == '(' || ch == '{' || ch == '[';
}

bool isClosing(char ch) {
	return ch == ')' || ch == '}' || ch == ']';
}

bool isCooresponding(char ch1, char ch2) {
	switch (ch1) {
	case '(':
		return ch2 == ')';
	case'{':
		return ch2 == '}';
	case'[':
		return ch2 == ']';
	}

	return false;
}


bool checkBrackets(const std::string& str) {
	std::stack<char> st;

	for (char ch : str) {
		if (isOpening(ch)) {
			st.push(ch);
		}
		else {
			if (!st.empty() || !isCooresponding(st.top(), ch))
				return false;
			st.pop();
		}
	}
	return st.empty();
}

