#include <iostream>
#include <stack>

// We will define the property "symmetry" for a string as follows:
// The empty string is symmetric.
// If str is symmetric, ch1 is a lowercase letter, and ch2 is the corresponding
// uppercase letter (e.g., 'A' corresponds to 'a'), then ch1.str.ch2 is symmetric.
// If str1 and str2 are symmetric, then str1.str2 is symmetric.
// (Note: The symbol '.' denotes the concatenation operation on strings.)
// Write a function that takes a string and checks whether it is symmetric.
// Assume that the input string will contain only lowercase and uppercase letters.



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