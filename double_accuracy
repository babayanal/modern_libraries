#include <iostream>
#include <cmath>
#include <limits>

int main() {
    // 1. First positive double
    double firstPositive = std::numeric_limits<double>::denorm_min();
    std::cout << "1) First positive double (denorm_min): " << firstPositive << "\n";

    // 2. Find first positive number where double and int differ by 1
    double x = 1.0;
    while (true) {
        int intPart = static_cast<int>(x);
        double diff = x - intPart;

        if (std::fabs(diff - 1.0) < 1e-12) {
            std::cout << "2) Found number: " << x << "\n";
            break;
        }

        double next = std::nextafter(x, std::numeric_limits<double>::infinity());
        if (next == x) {
            std::cout << "Reached limit without finding such a number.\n";
            break;
        }
        x = next;
    }

    return 0;
}
