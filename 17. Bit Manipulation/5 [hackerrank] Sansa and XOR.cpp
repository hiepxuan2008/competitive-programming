// Problem: Sansa and XOR
// Link: https://www.hackerrank.com/challenges/sansa-and-xor/problem
// Author: Mai Thanh Hiep
// Complexity: O(T * N), T <= 5, N <= 10^5

/*
    Idea:
    - XOR properties:
    x ^ x = 0
    x ^ 0 = x
    - We know that a number XOR with itself will give 0. Instead of calculating XOR subarray directly, we can
    count number of times each number appears in any subarray. If it appears an even number of times, then
    (x^x...^x) where there is an even number of "x" value will give 0. If there are an odd number of "x" values,
    the result will be x.
    * Case 1: n is even
    => Each element appears an even number of times throughout the subarrays, so the answer is 0.
    * Case 2: n is odd
    arr[0], arr[2], ..., arr[n] will appear an odd number of times
    arr[1], arr[3], ..., arr[n-1] will appear an even number of times
    Ex: We have array arr = [1, 2, 3]
    A = 1^2^3^(1^2)^(2^3)^(1^2^3)
      = 1^1^1^2^2^2^2^3^3^3

    1: appear 3 times
    2: appear 4 times
    3: appear 3 times

    A = 1 ^ 3 = 2
*/

#include <iostream>
using namespace std;
#define MAX 100000

int main() {
    int t;
    cin >> t;

    int n, x;
    int arr[MAX];
    while (t--) {
        cin >> n;

        for (int i = 0; i < n; i++)
            cin >> arr[i];

        if (n % 2 == 0) {
            cout << 0 << endl;
        } else {
            int res = 0;
            for (int i = 0; i < n; i += 2)
                res ^= arr[i];
            cout << res << endl;
        }
    }

    return 0;
}
