#include <iostream>
#include "separate_chaining_hash_map.hpp"

int main() {
    SeparateChainingHashMap<int, int> hm;
    hm.insert(1, 2);
    hm.insert(10, 50);
    hm.insert(1, 5);
    std::cout << hm.contains(2) << std::endl;
    hm.insert(2, 3);
    std::cout << hm.contains(2) << std::endl;
    hm.erase(2);
    std::cout << hm.contains(2) << std::endl;
    for (auto& pair : hm) {
        std::cout << pair.key << ": " << pair.value << std::endl;
    }
}
