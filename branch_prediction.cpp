//for running 
//g++ -O3 -march=native -std=c++17 -DNDEBUG -flto -funroll-loops -o branch_prediction branch_prediction.cpp

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cstdint>    
#include <iomanip>   

using namespace std;
using namespace std::chrono;

constexpr size_t N = 100000000; 

int main() {
    vector<uint8_t> data;
    try {
        data.resize(N);
    } catch (const bad_alloc& e) {
        cerr << "Allocation failed: " << e.what() << '\n';
        return 1;
    }
    // -------- Case 1: Predictable branch --------
    for (size_t i = 0; i < N; ++i) {
        data[i] = 1; 
    }

    long long sum = 0;
    auto start = steady_clock::now();

    for (size_t i = 0; i < N; ++i) {
        if (data[i]) {    
            sum++;
        }
    }
    cout.setf(std::ios::fixed); cout<<setprecision(3);
    cout << "Predictable branch time: "
         << (duration_cast<nanoseconds>(steady_clock::now() - start).count() / 1e6)
         << " ms (sum=" << sum << ")\n";

    // -------- Case 2: Unpredictable branch --------
    random_device rd;
    mt19937 gen(rd());
    for (size_t i = 0; i < N; ++i) {
        data[i] = static_cast<uint8_t>(gen() & 1);
    }

    sum = 0;
    start = steady_clock::now();
    for (size_t i = 0; i < N; ++i) {
        if (data[i]) {    
            sum++;
        }
    }
    cout << "Unpredictable branch time: "
         << (duration_cast<nanoseconds>(steady_clock::now() - start).count() / 1e6)
         << " ms (sum=" << sum << ")\n";

    // -------- Case 3: Branchless code --------
    sum = 0;
    start = steady_clock::now();
    for (size_t i = 0; i < N; ++i) {
        sum += data[i];    
    }
    cout << "Branchless code time: "
         << (duration_cast<nanoseconds>(steady_clock::now() - start).count() / 1e6)
         << " ms (sum=" << sum << ")\n";

    return 0;
}
