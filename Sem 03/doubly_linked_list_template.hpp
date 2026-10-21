#pragma once
#include <stdexcept>
#include <ostream>

template <class T>
class DoublyLinkedList {
public:
	struct Node {
		T value;
		Node* next = nullptr;
		Node* prev = nullptr;

		Node(const T& value, Node* prev = nullptr, Node* next = nullptr) :
			value(value), prev(prev), next(next) {
		}
	};

	~DoublyLinkedList() {
		Node* curr = head;
		while (curr) {
			Node* next = curr->next;
			delete curr;
			curr = next;
		}
	}

	Node* push_front(const T& val) {
		// since we haven't implemented an iterator yet, we will return a pointer to the head so that we could use the erase(...) function
		if (isEmpty()) {
			head = tail = new Node(val);
		}
		else {
			Node* toAdd = new Node(val);
			toAdd->next = head;
			head->prev = toAdd;
			head = toAdd;
		}
		return head;
	}

	Node* push_back(const T& val) {
		// since we haven't implemented an iterator yet, we will return a pointer to the head so that we could use the erase(...) function
		if (isEmpty()) {
			head = tail = new Node(val);
		}
		else {
			Node* toAdd = new Node(val);
			toAdd->prev = tail;
			tail->next = toAdd;
			tail = toAdd;
		}
		return tail;
	}

	void pop_front() {
		if (isEmpty()) throw std::logic_error("Linked list is empty!");

		Node* toDelete = head;
		if (head == tail) {
			head = tail = nullptr;
		}
		else {
			head = head->next;
			head->prev = nullptr;
		}
		delete toDelete;
	}
	void pop_back() {
		if (isEmpty()) throw std::logic_error("Linked list is empty!");

		Node* toDelete = tail;
		if (head == tail) {
			head = tail = nullptr;
		}
		else {
			tail = tail->prev;
			tail->next = nullptr;
		}
		delete toDelete;
	}

	void erase(Node* node) {
		if (!node) throw std::invalid_argument("Node cannot be null!");

		if (node == head) pop_front();
		else if (node == tail) pop_back();
		else {
			node->prev->next = node->next;
			node->next->prev = node->prev;
			delete node;
		}
	}

	void insert(Node* node, const T& val) {
		if (node == head) push_front(val);
		else if (node == tail) push_back(val);
		else {
			Node* toAdd = new Node(val);
			toAdd->prev = node->prev;
			toAdd->next = node;

			node->prev->next = toAdd;
			node->prev = toAdd;
		}
	}

	unsigned size() const {
		Node* curr = head;
		unsigned res = 0;
		while (curr) {
			res++;
			curr = curr->next;
		}
		return res;
	}

	bool isEmpty() const {
		return head == nullptr;
	}

	std::ostream& print(std::ostream& out = std::cout) const {
		Node* curr = head;
		while (curr) {
			out << curr->value << " ";
			curr = curr->next;
		}
		return out;
	}
private:
	Node* head = nullptr;
	Node* tail = nullptr;
};