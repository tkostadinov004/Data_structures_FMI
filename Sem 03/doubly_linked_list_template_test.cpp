#include <iostream>
#include "doubly_linked_list_template.hpp"

int main() {
	DoublyLinkedList<int> dll;
	dll.push_back(1);
	dll.push_back(2);
	DoublyLinkedList<int>::Iterator it = dll.push_back(3);
	DoublyLinkedList<int>::Iterator rem = dll.push_back(4);
	dll.push_back(5);
	dll.print();
	std::cout << std::endl;

	dll.erase(rem);
	dll.print();
	std::cout << std::endl;
	dll.insert(it, 100);
	dll.print();
}
