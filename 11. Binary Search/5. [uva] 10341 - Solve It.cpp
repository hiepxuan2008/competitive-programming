// Problem: 10341 - Solve It
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1282
// Solution: Mai Thanh Hiep
// Complexity:

#include <iostream>
#include <algorithm>
#include <math.h>       /* exp */
using namespace std;
#define EPSILON 1e-5

int p, q, r, s, t, u;

// f is a non-increasing function on [0,1]
double f(double x) {
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

void solve() {
    double left = 0;
    double right = 1.0d;
    while (left < right) {
        double mid = left + (right - left) / 2;
        double f0 = f(mid);
        if (abs(f0) < EPSILON) {
            cout.precision(5);
            cout << mid << endl;
            return;
        } else if (f0 > 0) { // -> since f is a non-increasing function -> so we find x on [0, mid]
            right = mid;
        } else {
            left = mid;
        }
    }

    cout << "No solution" << endl;
}

int main() {
    while (cin >> p) {
        cin >> q >> r >> s >> t >> u;

        solve();
    }

	return 0;
}
