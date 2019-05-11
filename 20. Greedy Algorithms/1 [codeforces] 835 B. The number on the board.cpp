// Problem: 835 B. The number on the board
// Link: https://codeforces.com/problemset/problem/835/B
// Author: Mai Thanh Hiep
// Complexity: O(LogN), N <= 10^100000

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int k;
string n;

int main() {
    cin >> k >> n;

    int digits_sum = 0;
    for (int i = 0; i < n.length(); i++) {
        digits_sum += n[i] - '0';
    }

    sort(n.begin(), n.end());

    int ans = 0;
    while (digits_sum < k) {
        digits_sum += '9' - n[ans];
        ans++;
    }

    cout << ans << endl;
    return 0;
}