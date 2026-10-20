#include <iostream>

class DoublyLinkedList {
public:
	struct Node {
		int value;
		Node* next = nullptr;
		Node* prev = nullptr;

		Node(int value, Node* prev = nullptr, Node* next = nullptr) :
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

	Node* push_front(int val) {
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

	Node* push_back(int val) {
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

	void insert(Node* node, int val) {
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

	friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList& dll);
private:
	Node* head = nullptr;
	Node* tail = nullptr;
};

std::ostream& operator<<(std::ostream& os, const DoublyLinkedList& dll) {
	const DoublyLinkedList::Node* curr = dll.head;
	while (curr) {
		os << curr->value << " ";
		curr = curr->next;
	}
	return os;
}

int main() {
	DoublyLinkedList dll;
	dll.push_back(1);
	dll.push_back(2);
	DoublyLinkedList::Node* rem = dll.push_back(3);
	DoublyLinkedList::Node* ins = dll.push_back(4);
	dll.push_back(5);
	std::cout << dll << std::endl;

	dll.erase(rem);
	std::cout << dll << std::endl;
	dll.insert(ins, 100);
	std::cout << dll;
}
