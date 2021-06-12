// Problem: 380 C. Sereja and Brackets
// Link: https://codeforces.com/problemset/problem/380/C
// Author: Mai Thanh Hiep
// Complexity: O(M * N), where M <= 10^6 is number of queries, N <= 10^5 is length of string (Time Limit Exceeded!)

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;
#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

int countCorrectBrackets(const string& str, int l, int r) {
    int open = 0;
    int ans = 0;
    for (int i = l; i <= r; ++i) {
        if (str[i] == '(') {
            ++open;
        } else {
            if (open > 0) {
                ans += 2;
                --open;
            }
        }
    }
    return ans;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);

    int m, l, r;
    string str;
    cin >> str;
    cin >> m;
    while (m-- > 0) {
        cin >> l >> r;
        cout << countCorrectBrackets(str, l - 1, r - 1) << endl;
    }
    return 0;
}