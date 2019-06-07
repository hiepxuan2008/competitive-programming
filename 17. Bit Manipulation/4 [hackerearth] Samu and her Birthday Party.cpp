// Author: Mai Thanh Hiep
// Problem: Samu and her Birthday Party
// Link: https://www.hackerearth.com/practice/basic-programming/bit-manipulation/basics-of-bit-manipulation/practice-problems/algorithm/samu-and-her-birthday-party-1/
// Complexity:			O(T * 2^K * N * K), T <= 10, K <= 10, N <= 500, 
//	=> Max operations:	O(10 * 1024 * 500 * 10) = 51200000, T=10, K=10, N=500

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <string.h> // for memset
using namespace std;

#define MAX 500
bool served[MAX];

// Get bit k th of x
int getBit(int x, int k) {
    return (x >> k) & 1;
}

int countBit1(int x) {
    int cnt = 0;
    while (x > 0) {
        cnt += x & 1;
        x = x >> 1;
    }
    return cnt;
}

bool isOptionOK(int option, int k, string* dishes, int n) {
    memset(served, 0, n);

    for (int i = 0; i < k; i++) { // O(N * K)
        if (getBit(option, i) == 1) {
            for (int j = 0; j < n; j++)
                if (dishes[j][i] == '1')
                    served[j] = true;
        }
    }

    for (int i = 0; i < n; i++)
        if (!served[i])
            return false;

    return true;
}

int main() {
    int T, n, k;
    cin >> T;

    string dishes[MAX];
    while (T--) {
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> dishes[i];
        }

        int ans = k;
        int allDishes = (1 << k) - 1;
        // brute force all options from 1 to 2^k-1
        for (int option = 1; option <= allDishes; option++) { // O(2^k) * O(N*K) = O(2^K * N * K), K <= 10, N <= 500 -> This is complexity of this solution
            if (isOptionOK(option, k, dishes, n)) { // O(N*K)
                ans = min(countBit1(option), ans);
            }
        }

        cout << ans << endl;
    }
    return 0;
}