#pragma once
#include <vector>
#include <list>

template <class K, class V>
class SeparateChainingHashMap {
	struct Pair {
		K key;
		V value;
	};

	std::hash<K> hash;
	std::vector<std::list<Pair>> buckets;
	unsigned elementsCount = 0;

	double loadFactor() const;
	void resize();
public:
	SeparateChainingHashMap() : buckets(1) {}

	class Iterator {
		std::vector<std::list<Pair>>& buckets;

		int bucketIndex;
		typename std::list<Pair>::iterator bucketIt;
	public:
		Iterator(std::vector<std::list<Pair>>& buckets, int bucketIndex, typename std::list<Pair>::iterator bucketIt) 
			: buckets(buckets), bucketIndex(bucketIndex), bucketIt(bucketIt) {}

		const Pair& operator*() { return *bucketIt; }
		Iterator& operator++();
		Iterator operator++(int dummy);
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
	};
	Iterator begin();
	Iterator end();

	void insert(const K& key, const V& val);
	bool contains(const K& key) const;
	bool erase(const K& key);
};

template<class K, class V>
double SeparateChainingHashMap<K, V>::loadFactor() const {
	return elementsCount / buckets.size();
}

template<class K, class V>
void SeparateChainingHashMap<K, V>::resize() {
	std::vector<std::list<Pair>> newBuckets(buckets.size() * 2);
	for (auto& bucket : buckets) {
		for (auto& el : bucket) {
			int hashCode = hash(el.key) % newBuckets.size();
			newBuckets[hashCode].push_back(el);
		}
	}
	buckets = std::move(newBuckets);
}
template<class K, class V>
typename SeparateChainingHashMap<K, V>::Iterator SeparateChainingHashMap<K, V>::begin() {
	auto it = Iterator(buckets, 0, buckets[0].begin());
	if (buckets[0].empty()) ++it;
	return it;
}

template<class K, class V>
typename SeparateChainingHashMap<K, V>::Iterator SeparateChainingHashMap<K, V>::end() {
	return Iterator(buckets, buckets.size(), buckets[buckets.size() - 1].end());
}

template<class K, class V>
void SeparateChainingHashMap<K, V>::insert(const K& key, const V& val) {
	if (loadFactor() > 0.75) resize();

	int hashCode = hash(key) % buckets.size();
	for (auto it = buckets[hashCode].begin(); it != buckets[hashCode].end(); ++it) {
		if (it->key == key) {
			it->value = val;
			return;
		}
	}
	buckets[hashCode].push_back({ key, val });
	elementsCount++;
}

template<class K, class V>
bool SeparateChainingHashMap<K, V>::contains(const K& key) const {
	int hashCode = hash(key) % buckets.size();
	for (auto it = buckets[hashCode].begin(); it != buckets[hashCode].end(); ++it) {
		if (it->key == key) return true;
	}
	return false;
}

template<class K, class V>
bool SeparateChainingHashMap<K, V>::erase(const K& key) {
	int hashCode = hash(key) % buckets.size();
	for (auto it = buckets[hashCode].begin(); it != buckets[hashCode].end(); ++it) {
		if (it->key == key) {
			buckets[hashCode].erase(it);
			elementsCount--;
			return true;
		}
	}
	return false;
}

template<class K, class V>
typename SeparateChainingHashMap<K, V>::Iterator& SeparateChainingHashMap<K, V>::Iterator::operator++() {
	++bucketIt;
	if (bucketIt != buckets[bucketIndex].end()) return *this;

	bucketIndex++;
	while (bucketIndex < buckets.size() && buckets[bucketIndex].empty()) {
		bucketIndex++;
	}
	if (bucketIndex < buckets.size()) bucketIt = buckets[bucketIndex].begin();
	else bucketIt = buckets[bucketIndex - 1].end();
	return *this;
}

template<class K, class V>
typename SeparateChainingHashMap<K, V>::Iterator SeparateChainingHashMap<K, V>::Iterator::operator++(int dummy) {
	Iterator old = *this;
	++(*this);
	return old;
}

template<class K, class V>
bool SeparateChainingHashMap<K, V>::Iterator::operator==(const Iterator& other) const {
	return bucketIndex == other.bucketIndex && bucketIt == other.bucketIt;
}

template<class K, class V>
bool SeparateChainingHashMap<K, V>::Iterator::operator!=(const Iterator& other) const {
	return !(*this == other);
}
