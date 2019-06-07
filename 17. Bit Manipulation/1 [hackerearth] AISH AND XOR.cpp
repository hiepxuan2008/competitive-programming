// Problem: AISH AND XOR
// Link: https://www.hackerearth.com/practice/basic-programming/bit-manipulation/basics-of-bit-manipulation/practice-problems/algorithm/aish-and-xor-2/
// Author: Mai Thanh Hiep
// Complexity: O(N + Q), Q <= N <= 100000

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, q, l, r, x;
    cin >> n;
    vector<int> prefixSum(n);
    for (int i = 0; i < n; i++) { // O(N)
        cin >> x;
        if (i > 0) {
            prefixSum[i] = prefixSum[i - 1] + x;
        } else {
            prefixSum[i] = x;
        }
    }

    int numOne = 0;
    int numZero = 0;
    cin >> q;
    while (q--) { // O(Q)
        cin >> l >> r;
        --l; --r;

        if (l > 0)
            numOne = prefixSum[r] - prefixSum[l - 1];
        else
            numOne = prefixSum[r];

        numZero = (r - l + 1) - numOne;

        cout << (numOne % 2) << " " << numZero << endl;
    }

    return 0;
}