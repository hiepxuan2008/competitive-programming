// Problem: Queries with Fixed Length
// Link: https://www.hackerrank.com/challenges/queries-with-fixed-length/problem
// Author: Mai Thanh Hiep
// Complexity: O(Q * N), where Q <= 100 is number of queries, N <= 10^5 is the size of array.

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <deque>
using namespace std;

const int MAXN = 100010;
int arr[MAXN];

void solve(int n, int k) {
    deque<int> dq;
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k - 1) {
            ans = min(ans, arr[dq.front()]);

            // remove the last element of range k
            if (i - dq.front() + 1 >= k) dq.pop_front();
        }
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);

    int n, q, d;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < q; i++) {
        cin >> d;
        solve(n, d);
    }
    return 0;
}