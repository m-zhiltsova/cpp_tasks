#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    float d = b^2 + 4*a*c;
    if (d > 0) {
        cout << ((b + sqrt(d)) /2/a);
        cout << "   ";
        cout << ((b - sqrt(d)) /2/a) << endl;
    }
    else if (d == 0) {
        cout << (b/2/a) << endl;
    }    
    else {
        cout << "No real numbers" << endl;
    }
    return 0;
}
