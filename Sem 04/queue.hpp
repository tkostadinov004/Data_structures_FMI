#pragma once
#include <stdexcept>

template <class T>
class Queue {
	T* data;
	unsigned size = 0;
	unsigned capacity = 1;

	int get = 0;
	int put = -1;

	void resize(unsigned newCapacity) {
		T* newData = new T[newCapacity];
		int idx = 0;
		for (int i = get; i < capacity; i++) {
			newData[idx++] = data[i];
		}
		for (int i = 0; i < get; i++) {
			newData[idx++] = data[i];
		}

		delete[] data;
		data = newData;
		capacity = newCapacity;
		get = 0;
		put = size - 1;
	}
public:
	Queue() {
		data = new T[capacity];
	}

	~Queue() {
		delete[] data;
		size = 0;
		capacity = 0;
	}

	void push(const T& value) {
		if (size == capacity) {
			resize(capacity * 2);
		}

		put = (put + 1) % capacity;
		data[put] = value;
		size++;
	}

	void pop() {
		if (empty()) throw std::logic_error("Queue is empty!");

		get = (get + 1) % capacity;
		size--;
	}

	const T& front() const {
		if (empty()) throw std::logic_error("Queue is empty!");

		return data[get];
	}

	int getSize() const {
		return size;
	}

	bool empty() const {
		return size == 0;
	}
};
