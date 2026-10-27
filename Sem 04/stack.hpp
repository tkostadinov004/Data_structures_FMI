#pragma once
#include <stdexcept>

template <class T>
class Stack {
public:
	struct Node {
		T value;
		Node* next;
		Node(const T& value) : value(value), next(nullptr) {}
	};

	void push(const T& value) {
		if (!head) {
			head = new Node(value);
		}
		else {
			Node* newNode = new Node(value);
			newNode->next = head;
			head = newNode;
		}
		size++;
	}

	void pop() {
		if (empty()) throw std::logic_error("Stack is empty!");

		Node* toDelete = head;
		head = head->next;
		delete toDelete;
		size--;
	}

	const T& top() const {
		if (empty()) throw std::logic_error("Stack is empty!");

		return head->value;
	}

	int getSize() const {
		return size;
	}

	bool empty() const {
		return head == nullptr; // size == 0;
	}
private:
	Node* head = nullptr;
	int size = 0;
};
