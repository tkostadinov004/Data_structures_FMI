#include <iostream>
#include <vector>
#include <stack>
#include <queue>

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

	class Iterator {
		Node* node;
	public:
		Iterator(Node* node) : node(node) {}

		Iterator& operator++() {
			node = node->next;
			return *this;
		}
		Iterator operator++(int) {
			Iterator old = *this;
			++(*this);
			return old;
		}
		
		Iterator& operator--() {
			node = node->prev;
			return *this;
		}
		Iterator operator--(int) {
			Iterator old = *this;
			--(*this);
			return old;
		}

		int& operator*() {
			return node->value;
		}

		Node* getPtr() {
			return node;
		}

		bool operator==(const Iterator& other) const {
			return node == other.node;
		}

		bool operator!=(const Iterator& other) const {
			return !(*this == other);
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

	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}

	Iterator push_front(int val) {
		if (isEmpty()) {
			head = tail = new Node(val);
		}
		else {
			Node* toAdd = new Node(val);
			toAdd->next = head;
			head->prev = toAdd;
			head = toAdd;
		}
		return Iterator(head);
	}

	Iterator push_back(int val) {
		if (isEmpty()) {
			head = tail = new Node(val);
		}
		else {
			Node* toAdd = new Node(val);
			toAdd->prev = tail;
			tail->next = toAdd;
			tail = toAdd;
		}
		return Iterator(tail);
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

	void erase(Iterator it) {
		if (it == end()) throw std::invalid_argument("Node cannot be null!");
		
		Node* node = it.getPtr();
		if (node == head) pop_front();
		else if (node == tail) pop_back();
		else {
			node->prev->next = node->next;
			node->next->prev = node->prev;
			delete node;
		}
	}

	void insert(Iterator it, int val) {
		Node* node = it.getPtr();
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
	DoublyLinkedList::Iterator it = dll.push_back(3);
	DoublyLinkedList::Iterator rem = dll.push_back(4);
	dll.push_back(5);
	std::cout << dll << std::endl;

	dll.erase(rem);
	std::cout << dll << std::endl;
	dll.insert(it, 100);
	std::cout << dll;
}
