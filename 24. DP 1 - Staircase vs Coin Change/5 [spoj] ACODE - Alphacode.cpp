// Problem: ACODE - Alphacode
// Link: https://www.spoj.com/problems/ACODE/
// Author: Mai Thanh Hiep
// Complixity: T * O(N), N <= MAX = 5000

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAX 5001

int main() {
    string s;
    int n;
    long long dp[MAX];
    while (cin >> s && s != "0") {
        n = s.size();
        dp[0] = 1;
        int index;
        for (int i = 1; i <= n; i++) {
            dp[i] = 0;
            index = i - 1;
            if (s[index] != '0')
                dp[i] += dp[i - 1];
            if (index - 1 >= 0 && (s[index - 1] == '1' || s[index - 1] == '2' && s[index] <= '6'))
                dp[i] += dp[i - 2];
        }
        cout << dp[n] << endl;
    }

    return 0;
}