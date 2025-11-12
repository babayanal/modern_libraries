#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x = pow(2, 53);
    cout.precision(17);
    cout << "2^53 = " << x << endl;
    cout << "Next double after 2^53: " << nextafter(x, INFINITY) << endl;
    cout << "Difference: " << nextafter(x, INFINITY) - x << endl;
    return 0;
}
