#include <stack>
#include <string>
using namespace std;

//Given a balanced parentheses string s, return the score of the string.
//The score of a balanced parentheses string is based on the following rule :
//"()" has score 1
//AB has score A + B, where A and B are balanced parentheses strings.
//(A)has score 2 * A, where A is a balanced parentheses string.

class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> scoreSt;
        int score = 0;
        for (int i = 0;i < s.size();i++) {
            if (s[i] == '(') {
                scoreSt.push(score);
                score = 0;
            }
            else {
                score = scoreSt.top() + max(2 * score, 1);
                scoreSt.pop();
            }
        }
        return score;
    }
};