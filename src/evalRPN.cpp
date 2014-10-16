/*
 Evaluate Reverse Polish Notation

 Evaluate the value of an arithmetic expression in Reverse Polish Notation.

 Valid operators are +, -, *, /. Each operand may be an integer or another expression.

 Some examples:
 ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
 ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

 */

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <cstdlib>

using namespace std;

//static int eval(vector<string> &tokens, int pos) {
//
//}
class Solution {
public:
	static bool op(const string& s) {
		return "-" == s || "+" == s || "*" == s || "/" == s;
	}

	int evalRPN(vector<string> &tokens) {
		stack<int> stack;
		int left, right;
		for (size_t i = 0; i < tokens.size(); ++i) {
			string& x = tokens[i];
			if (!op(x)) {
				stack.push(atoi(x.c_str()));
			} else {
				right = stack.top();
				stack.pop();
				left = stack.top();
				stack.pop();
				switch (x[0]) {
				case '+':
					stack.push(left + right);
					break;
				case '-':
					stack.push(left - right);
					break;
				case '*':
					stack.push(left * right);
					break;
				case '/':
					stack.push(left / right);
					break;
				default:
					assert(true);
					break;
				}
			}
		}
		return stack.top();
	}
};

int main(int argc, char **argv) {

	vector<string> toks = { "-1", "1", "*", "-1", "+" }; //{ "4", "13", "5", "/", "+" }; // {"2", "1", "+", "3", "*"};
	cout << Solution().evalRPN(toks) << endl;
	return 0;
}

