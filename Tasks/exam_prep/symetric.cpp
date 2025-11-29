#include <iostream>
#include <stack>

//Ще дефинираме свойството симетричност за string както следва:
//Празният string е симетричен
//Ако str е симетричен, ch1 е малка буква и ch2 е съответстващата 
// й главна буква(пр: 'A' съответства на 'a'), то ch1.str.ch2 е симетричен
//Ако str1 и str2 са симетрични, то str1.str2 е симетричен
//(Забележка: Със знак ' . ' бележим операцията конкатенация на string - ове.)
//Да се напише функция, която приема string и проверява дали той е симетричен.
// Приемете, че няма да получите string със символи, различни от малки и главни букви.


bool isSymetric(const std::string& str) {
	std::stack<char> st;
	for (char ch : str) {
		if (islower(ch))
			st.push(ch);
		else {
			ch = tolower(ch);
			if (!st.empty() && st.top() == ch) {
				st.pop();
			}
			return false;
		}
	}
	return st.empty();
}

int main()
{
	std::cout << isSymetric("qweEWQrtTR");
}