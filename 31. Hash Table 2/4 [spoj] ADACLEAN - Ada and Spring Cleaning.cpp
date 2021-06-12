// Problem: ADACLEAN - Ada and Spring Cleaning
// Link: https://www.spoj.com/problems/ADACLEAN/
// Author: Mai Thanh Hiep
// Complexity: O(T * N), where T is number of testcase, where N <= 10^5 is length of string

#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 5;
ll BASE = 27;
ll preHash[MAXN];
ll POW[MAXN];

ll getHash(int l, int r) {
    ++l;
    ++r;
    return preHash[r] - preHash[l - 1] * POW[r - l + 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    
    string str;
    int t, n, k;
    cin >> t;
    while (t-- > 0) {
        cin >> n >> k;
        cin >> str;
        preHash[0] = 0;
        POW[0] = 1;
        unordered_set<ll> set;
        for (int i = 0; i < n; i++) {
            preHash[i + 1] = preHash[i] * BASE + str[i] - 'a';
            POW[i + 1] = POW[i] * BASE;
            if (i >= k - 1) {
                set.insert(getHash(i - k + 1, i));
            }
        }
        cout << set.size() << endl;
    }
    return 0;
}