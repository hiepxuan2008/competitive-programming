// Problem: B. Roma and Changing Signs
// Link: https://codeforces.com/problemset/problem/262/B
// Author: Mai Thanh Hiep
// Complexity:
//              Time: O(N)
//              Space: O(1)

#include <iostream>
#include <algorithm>
using namespace std;
#define INF 10000

int main() {
    int n, k, x;
    cin >> n >> k;

    int ans = 0;
    int absMin = INF;
    for (int i = 0; i < n; i++) { // O(N) -> This is time complexity of this solution
        cin >> x;
        absMin = min(absMin, abs(x));
        if (x < 0 && k > 0) {
            ans -= x;
            k--;
        } else {
            ans += x;
        }
    }

    if (k % 2 == 1) { // change the sign of absMin from plus to minus
        ans -= 2 * absMin;
    }

    cout << ans << endl;

    return 0;
}