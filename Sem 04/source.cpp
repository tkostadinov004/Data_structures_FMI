#include <iostream>
#include "stack.hpp"
#include "queue.hpp"

void stackTest() {
	Stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);

	while (!st.empty()) {
		std::cout << st.top() << std::endl;
		st.pop();
	}
}

void queueTest() {
	Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	while (!q.empty()) {
		std::cout << q.front() << std::endl;
		q.pop();
	}
}

int main() {
	std::cout << "Stack: " << std::endl;
	stackTest();
	std::cout << "Queue: " << std::endl;
	queueTest();
}
