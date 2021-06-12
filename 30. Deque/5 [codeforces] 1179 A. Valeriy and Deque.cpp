// Problem: 1179 A. Valeriy and Deque
// Link: https://codeforces.com/problemset/problem/1179/A
// Author: Mai Thanh Hiep
// Complexity: O(N + Q), where N <= 10^5 is the size of array, Q <= 3 * 10^5 is the number of queries.

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>    // std::min_element, std::max_element
using namespace std;

typedef long long ll;
const int MAXN = 1e5+5;

int arr[MAXN];

void solve(int n, vector<ll>& queries) {
    int maxElement = *max_element(arr, arr + n);
    deque<int> dq;
    for (int i = 0; i < n; ++i) {
        dq.push_back(arr[i]);
    }
    vector<pair<int, int>> resAtOperation;
    int steps = 0; // number of steps so that in the future A will always be a maximum element
    while (dq.front() != maxElement) { // O(N)
        ++steps;
        int A = dq.front(); dq.pop_front();
        int B = dq.front(); dq.pop_front();
        resAtOperation.emplace_back(A, B);
        if (B > A) swap(A, B);
        dq.push_front(A);
        dq.push_back(B);
    }
    vector<int> remainArr;
    dq.pop_front(); // Now dq.front() always is A, B will be an element of (n-1) remain elements in cycle order. -> pop A to create remainArr.
    while (!dq.empty()) {
        remainArr.push_back(dq.front());
        dq.pop_front();
    }
    vector<pair<int, int>> res;
    for (ll m : queries) { // O(Q)
        --m; // zero-based indexing
        if (m < steps) {
            res.push_back(resAtOperation[m]);
        } else { // m >= steps
            m = (m - steps) % (n-1);
            res.emplace_back(maxElement, remainArr[m]);
        }
    }
    for (auto & re : res) {
        cout << re.first << " " << re.second << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    vector<ll> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i];
    }
    solve(n, queries);
    return 0;
}