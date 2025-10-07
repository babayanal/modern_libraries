#include <iostream>
#include <new>      // for ::operator new, ::operator delete
#include <utility>  // for std::move

template <typename T>
class SimpleVector {
private:
    T* data;         // pointer to allocated memory
    size_t sz;       // number of elements
    size_t cap;      // total capacity

public:
    // Constructor
    SimpleVector() : data(nullptr), sz(0), cap(0) {}

    // Destructor
    ~SimpleVector() {
        clear();
        ::operator delete(data);
    }

    // Return number of elements
    size_t size() const { return sz; }

    // Return current capacity
    size_t capacity() const { return cap; }

    // Add an element
    void push_back(const T& value) {
        if (sz == cap)
            duplicate();  // double capacity if full

        // Construct element in-place
        new(&data[sz]) T(value);
        ++sz;
    }

    // Duplicate (double) the capacity
    void duplicate() {
        size_t newCap = (cap == 0) ? 1 : cap * 2;
        T* newData = static_cast<T*>(::operator new(newCap * sizeof(T)));

        // Move existing elements to new memory
        for (size_t i = 0; i < sz; ++i) {
            new(&newData[i]) T(std::move(data[i]));
            data[i].~T();
        }

        ::operator delete(data);
        data = newData;
        cap = newCap;
    }

    // Clear vector contents
    void clear() {
        for (size_t i = 0; i < sz; ++i)
            data[i].~T();
        sz = 0;
    }

    // Index operator
    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }
};

int main() {
    SimpleVector<int> vec;

    for (int i = 1; i <= 8; ++i) {
        vec.push_back(i * 10);
        std::cout << "Added: " << i * 10
                  << " | size = " << vec.size()
                  << " | capacity = " << vec.capacity() << '\n';
    }

    std::cout << "\nElements: ";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << '\n';
}
