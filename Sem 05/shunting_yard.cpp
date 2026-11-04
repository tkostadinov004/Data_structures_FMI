#include <iostream>
#include <stack>
#include <string>

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

bool isOp(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool hasGreaterThanOrEqualPriority(char op1, char op2) {
	return (op1 == '*' || op1 == '/') || (op2 == '+' || op2 == '-');
}

int evaluateRPN(const std::string& s) {
	std::stack<int> st;
	int idx = 0;
	while (idx < s.size()) {
		if (s[idx] == ' ') {
			idx++;
			continue;
		}

		if (isDigit(s[idx])) {
			int number = 0;
			while (idx < s.size() && isDigit(s[idx])) {
				number = number * 10 + (s[idx] - '0');
				idx++;
			}
			st.push(number);
		}
		else {
			int second = st.top();
			st.pop();
			int first = st.top();
			st.pop();

			switch (s[idx]) {
			case '+':
				st.push(first + second);
				break;
			case '-':
				st.push(first - second);
				break;
			case '*':
				st.push(first * second);
				break;
			case '/':
				st.push(first / second);
				break;
			}
		}
		idx++;
	}
	return st.top();
}

std::string shuntingYard(const std::string& s) {
	std::string res;
	std::stack<char> st;

	int idx = 0;
	while (idx < s.size()) {
		if (s[idx] == ' ') {
			idx++;
			continue;
		}

		if (isDigit(s[idx])) {
			std::string number;
			while (idx < s.size() && isDigit(s[idx])) {
				number += s[idx++];
			}
			res += number + " ";
			idx--;
		}
		else if (isOp(s[idx])) {
			while (!st.empty() && st.top() != '(' &&
				hasGreaterThanOrEqualPriority(st.top(), s[idx])) {
				res.push_back(st.top());
				res.push_back(' ');
				st.pop();
			}
			st.push(s[idx]);
		}
		else if (s[idx] == '(') {
			st.push(s[idx]);
		}
		else {
			while (!st.empty() && st.top() != '(') {
				res.push_back(st.top());
				res.push_back(' ');
				st.pop();
			}
			st.pop();
		}
		idx++;
	}

	while (!st.empty()) {
		res.push_back(st.top());
		res.push_back(' ');
		st.pop();
	}
	return res;
}

int main() {
	std::cout << evaluateRPN(shuntingYard("6-1+4*5+9+2*(3+4)"));
}
