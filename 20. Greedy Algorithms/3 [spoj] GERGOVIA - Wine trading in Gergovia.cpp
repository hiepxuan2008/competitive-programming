// Problem: Wine trading in Gergovia
// Link: https://www.spoj.com/problems/GERGOVIA/
// Author: Mai Thanh Hiep
// Complexity: 

#include <iostream>
using namespace std;

int main() {
    int n;
    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }

        long long res = 0, s = 0;
        for (int i = 0, x; i < n; ++i) {
            res += abs(s);
            cin >> x;
            s += x;
        }

        cout << res << endl;
    }

    return 0;
}