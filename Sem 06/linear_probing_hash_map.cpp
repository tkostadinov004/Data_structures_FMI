#include <iostream>
#include <vector>

class LinearProbingHashMap {
	using Pair = std::pair<int, int>;
	struct Optional {
		Pair pair;
		bool tombstone = false;
		bool isActive = false;
	};

	std::hash<int> hash;
	std::vector<Optional> table;
	unsigned jumpFactor = 3;
	unsigned elementsCount = 0;
	double loadFactor() {
		return elementsCount / table.size();
	}
	void resize() {
		std::vector<Optional> newTable(table.size() * 2);
		for (auto& opt : table) {
			if (opt.isActive && !opt.tombstone) {
				insert(newTable, opt.pair.first, opt.pair.second);
			}
		}
		table = std::move(newTable);
	}
	void insert(std::vector<Optional>& table, int key, int value) {
		unsigned index = hash(key) % table.size();
		while (table[index].isActive && !table[index].tombstone) {
			if (table[index].pair.first == key) {
				table[index].pair.second = value;
				return;
			}
			index = (index + jumpFactor) % table.size();
		}
		table[index] = Optional{ {key, value}, false, true };
		elementsCount++;
	}
public:
	LinearProbingHashMap() : table(1) {}

	class Iterator {
		std::vector<Optional>& table;

		std::vector<Optional>::iterator it;
	public:
		Iterator(std::vector<Optional>& table, std::vector<Optional>::iterator it) : table(table), it(it) {}

		const Pair& operator*() { return (*it).pair; }

		Iterator& operator++() {
			++it;
			while (it != table.end() && (!it->isActive || it->tombstone)) {
				++it;
			}
			return *this;
		}

		Iterator operator++(int dummy) {
			Iterator old = *this;
			++(*this);
			return old;
		}

		bool operator==(const Iterator& other) {
			return it == other.it;
		}

		bool operator!=(const Iterator& other) {
			return !(*this == other);
		}
	};
	Iterator begin() {
		std::vector<Optional>::iterator it = table.begin();
		if (!table[0].isActive || table[0].tombstone) ++it;
		return Iterator(table, it);
	}
	Iterator end() { return Iterator(table, table.end()); }

	void insert(int key, int value) {
		if (loadFactor() > 0.75) resize();

		insert(table, key, value);
	}

	bool search(int key) {
		unsigned index = hash(key) % table.size();
		unsigned start = index;
		while (table[index].isActive) {
			if (!table[index].tombstone && table[index].pair.first == key) return true;

			index = (index + jumpFactor) % table.size();
			if (index == start) break;
		}
		return false;
	}

	bool remove(int key) {
		unsigned index = hash(key) % table.size();
		unsigned start = index;
		while (table[index].isActive) {
			if (!table[index].tombstone && table[index].pair.first == key) {
				table[index].tombstone = true;
				elementsCount--;
				return true;
			}

			index = (index + jumpFactor) % table.size();
			if (index == start) break;
		}
		return false;
	}
};

int main() {
	LinearProbingHashMap hm;
	hm.insert(1, 2);
	hm.insert(3, 4);
	for (auto& pair : hm) {
		std::cout << pair.first << " " << pair.second << "\n";
	}
}
