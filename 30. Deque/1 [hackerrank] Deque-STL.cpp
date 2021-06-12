// Problem: Deque-STL
// Link: https://www.hackerrank.com/challenges/deque-stl/problem
// Author: Mai Thanh Hiep
// Complexity: O(T * N), where T <= 1000 is number of testcases, N <= 10000 is the size of array.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
using namespace std;

const int MAXN = 10010;
int arr[MAXN];

void solve(int n, int k) {
    deque<int> dq;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        // Eliminate elements less or equal to arr[i]
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }

        // Push index of current nums[i] to the deque
        dq.push_back(i);

        // if reach enough range size k -> add the result
        if (i >= k - 1) {
            ans.push_back(arr[dq.front()]);

            // remove the last element of range k
            if (i - dq.front() + 1 >= k) dq.pop_front();
        }
    }
    for (int an : ans) {
        cout << an << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);

    int t, n, k;
    cin >> t;
    while (t-- > 0) {
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        solve(n, k);
    }
    return 0;
}