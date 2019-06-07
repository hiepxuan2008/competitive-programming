// Author: Mai Thanh Hiep
// Problem: Power of Two
// Link: https://www.hackerearth.com/challenges/competitive/thoughtworks-singapore-codeathon-2015/algorithm/power-of-two-4/
// Complexity: T * O(N), T <= 1000, N <= 200

#include <iostream>
using namespace std;

#define MAX 200
#define NUM_BITS 32

int getBit(int num, int k) {
    return (num >> k) & 1;
}

bool solve(int* arr, int n) {
    // Check all possible combine that bit i-th is set
    for (int i = 0; i < NUM_BITS; i++) {
        int mask = 0xffffffff; // all bits 1
        for (int j = 0; j < n; j++) {
            if (getBit(arr[j], i) == 1) { // bit i-th is set
                mask &= arr[j];
            }
        }

        if (mask == (1 << i)) // mask == 2^i
            return true;
    }
    return false;
}

int main() {
    int t, n;
    cin >> t;

    int arr[MAX];
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        cout << (solve(arr, n) ? "YES" : "NO") << endl;
    }

    return 0;
}
