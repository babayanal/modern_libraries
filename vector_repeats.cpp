#include <iostream>
#include <vector>
#include <unordered_map>

void findRepeating(const std::vector<int>& v) {
    std::unordered_map<int, int> freq;

    // Count occurrences
    for (int num : v) {
        freq[num]++;
    }

    // Print repeating elements
    std::cout << "Repeating elements: ";
    bool found = false;
    for (auto& [num, count] : freq) {
        if (count > 1) {
            std::cout << num << " ";
            found = true;
        }
    }

    if (!found) std::cout << "None";
    std::cout << "\n";
}

int main() {
    std::vector<int> v1 = {1, 2, 3, 4, 2};     // 1 repeating element
    std::vector<int> v2 = {5, 6, 7, 5, 8, 6};  // 2 repeating elements

    std::cout << "Example 1:\n";
    findRepeating(v1);

    std::cout << "Example 2:\n";
    findRepeating(v2);

    return 0;
}
