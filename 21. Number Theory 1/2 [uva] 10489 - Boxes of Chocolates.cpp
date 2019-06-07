// Problem: 10489 - Boxes of Chocolates
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1430
// Author: Mai Thanh Hiep
// Complexity: O(T * B * K); T, B, K <= 100

#include <iostream>
using namespace std;

int main() {
    int t, n, b, k, a, z;
    cin >> t;

    while (t--) {
        cin >> n >> b;
        int ans = 0;
        while (b--) {
            cin >> k;
            z = 1;
            while (k--) {
                cin >> a;
                z *= a, z %= n;
            }
            ans += z, ans %= n;
        }
        cout << ans << endl;
    }

    return 0;
}