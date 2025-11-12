#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "Smallest positive double: "
         << numeric_limits<double>::denorm_min() << endl;
    return 0;
}
