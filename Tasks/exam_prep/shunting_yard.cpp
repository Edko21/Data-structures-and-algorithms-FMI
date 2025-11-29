#include <iostream>
#include <deque>
#include <stack>

//Да се напише функция, която приема string, представляващ математичен израз, 
// записан с инфиксен запис. Функцията трябва да изчислява стойността на израза 
// или да съобщава за грешка при невалиден израз.

int applyOperatiron(char operation, int first, int second) {
	switch (operation) {
	case '+':
		return first + second;
	case'-':
		return first - second;
	case'*':
		return first * second;
	case'/':
		return first / second;
	default:
		throw std::exception("invalid");
	}
}

int revPolishNotation(std::string& str) {
	std::stack<int> st;
	for (char ch : str) {
		if (std::isdigit(ch)) {
			st.push(ch - '0');
		}
		else {
			if (st.size() < 2) {
				throw std::exception("invalid arguments");
			}
			int second = st.top();
			st.pop();
			int first = st.top();
			st.pop();

			st.push(applyOperatiron(ch, first, second));
		}
	}
	if (st.size() != 1)
		throw std::exception("invalid arguments count");
	return st.top();
}


unsigned int operationPriority(char operation) {
	switch (operation) {
	case'+':
	case'-':
		return 1;

	case'*':
	case'/':
		return 2;

	case'(':
		return 0;

	default:
		throw std::exception("invalid");
	}
}

bool isProcceding(char priorityOperation, char operation) {
	return operationPriority(priorityOperation) >= operationPriority(operation);
}

int evalExpression(const std::string& str) {
	std::stack<char> operations;
	std::string res;

	for (char ch : str) {
		if (ch == '(')
			operations.push(ch);
		else if (ch == ')') {
			if (!operations.empty() && operations.top() != '(') {
				res.push_back(operations.top());
				operations.pop();
			}
			if (operations.empty())
				throw std::exception("invalid");
			operations.pop();
		}
		else if (isdigit(ch))
			res.push_back(ch);
		else {
			while (!operations.empty() && isProcceding(operations.top(), ch)) {
				res.push_back(operations.top());
				operations.pop();
			}
			operations.push(ch);
		}
	}
	while (!operations.empty()) {
		res.push_back(operations.top());
		operations.pop();
	}
	return revPolishNotation(res);
}

int main()
{
	std::cout << evalExpression("(3-5*4+7)/3");
}