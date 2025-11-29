#include <iostream>
#include <deque>
#include <stack>

//Да се напише функция, която приема string, представляващ математически израз,
// записан в обратен полски запис. Функцията трябва да изчислява стойността на 
// израза или да съобщава за грешка при невалиден израз.

//helper funct if we cant use std::isdigit()
bool isDigit(char ch) {
	return (ch >= '0' && ch <= '9');
}

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
		else{
			if (st.size() < 2) {
				std::exception("invalid arguments");
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

int main()
{
	std::cout << revPolishNotation("345*-7+3/");
}