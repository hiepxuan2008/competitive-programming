// Problem: 285C. Building Permutation
// Link: https://codeforces.com/problemset/problem/285/C
// Author: Mai Thanh Hiep
// Complexity: O(NLogN)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // sort in increasing order
    sort(arr.begin(), arr.end()); // O(NLogN) -> This is complexity of this problem

    long long moves = 0;
    for (int i = n; i > 0; i--) {
        moves += abs(i - arr[i - 1]);
    }
    cout << moves << endl;

    return 0;
}