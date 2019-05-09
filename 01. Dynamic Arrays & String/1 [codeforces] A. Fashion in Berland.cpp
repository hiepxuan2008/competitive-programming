// Problem: A. Fashion in Berland
// Link: http://codeforces.com/contest/691/problem/A
// Solution: Mai Thanh Hiep

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int x;
    int nZero = 0;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x == 0)
            nZero++;
    }

    if (n == 1) {
        cout << (nZero == 0 ? "YES" : "NO") << endl;
    } else {
        cout << (nZero == 1 ? "YES" : "NO") << endl;
    }

    return 0;
}