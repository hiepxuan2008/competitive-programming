// Problem: TNVFC1M - Miraculous
// Link: https://www.spoj.com/problems/TNVFC1M/
// Author: Mai Thanh Hiep
// Complexity: O(Q * N), where Q is number of testcases, N <= 10^4 is the size of array.

#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAXN = 1e4 + 5;
int cost[MAXN], f[MAXN];

int main() {
//    fin;
    int n, h, b, e;
    while (cin >> n >> h >> b >> e) {
        for (int i = 1; i <= n; ++i) cin >> cost[i];
        deque<int> dq;
        for (int t = n; t >= 1; --t) { // O(N)
            f[t] = 1;
            while (!dq.empty() && t + h - 1 < dq.front()) { // Remove time points that current `t` can't reach to
                dq.pop_front();
            }
            while (!dq.empty() && cost[t] < cost[dq.back()]) {
                int liveAmount = t + h - dq.back();
                int amount = min(liveAmount, f[dq.back()]);
                f[t] += amount;
                f[dq.back()] -= amount;
                dq.pop_back();
            }
            dq.push_back(t);
        }
        for (int t = b; t <= e; ++t)
            cout << f[t] << ' ';
        cout << '\n';
    }
    return 0;
}