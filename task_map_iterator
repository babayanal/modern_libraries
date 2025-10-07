#include <iostream>
#include <vector>
#include <utility>

template <typename K, typename V>
class SimpleMap {
private:
    std::vector<std::pair<K, V>> data; // no ordering

public:
    // Insert element (doesn't check duplicates for simplicity)
    void insert(const K& key, const V& value) {
        data.emplace_back(key, value);
    }

    // Iterator inner class
    class Iterator {
    private:
        typename std::vector<std::pair<K, V>>::iterator it;

    public:
        explicit Iterator(typename std::vector<std::pair<K, V>>::iterator init) : it(init) {}

        // Dereference
        std::pair<K, V>& operator*() { return *it; }
        std::pair<K, V>* operator->() { return &(*it); }

        // Increment
        Iterator& operator++() { ++it; return *this; }

        // Comparison
        bool operator!=(const Iterator& other) const { return it != other.it; }
        bool operator==(const Iterator& other) const { return it == other.it; }
    };

    // begin() and end()
    Iterator begin() { return Iterator(data.begin()); }
    Iterator end() { return Iterator(data.end()); }

    // Optional: find element (O(n))
    V* find(const K& key) {
        for (auto& kv : data)
            if (kv.first == key)
                return &kv.second;
        return nullptr;
    }
};

int main() {
    SimpleMap<int, std::string> mymap;
    mymap.insert(42, "forty-two");
    mymap.insert(7, "seven");
    mymap.insert(100, "hundred");

    // Iterate O(n)
    for (auto& [key, value] : mymap) {
        std::cout << key << " => " << value << '\n';
    }

    // Lookup example
    if (auto* v = mymap.find(7))
        std::cout << "Found key 7 => " << *v << '\n';
}
