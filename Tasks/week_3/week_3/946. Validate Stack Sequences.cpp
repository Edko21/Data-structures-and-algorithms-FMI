#include<vector>
#include<stack>
using namespace std;

//Given two integer arrays pushed and popped
// each with distinct values, return true if 
// this could have been the result of a sequence 
// of push and pop operations on an initially empty stack, or false otherwise.

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> s;
        int poppedCnt = 0;

        for (int p : pushed)
            s.push(p);

        while (!s.empty() && s.top() == popped[poppedCnt]) {
            poppedCnt++;
            s.pop();
        }
        return s.empty() && poppedCnt == popped.size();
    }
};