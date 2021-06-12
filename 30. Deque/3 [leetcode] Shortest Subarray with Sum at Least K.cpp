// Problem: Shortest Subarray with Sum at Least K
// Link: https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
// Author: Mai Thanh Hiep
// Complexity: O(N), where N <= 50000 is the size of array.

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include <climits>
using namespace std;

class Solution {
public:
    int shortestSubarray(vector<int>& arr, int k) {
        deque<pair<int, int>> dq;
        int n = arr.size();
        int sum = 0;
        int ans = INT_MAX;
        int l = 0;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
            dq.emplace_back(arr[i], i);
            while (!dq.empty() && dq.back().first < 0) { // Merge
                int lastValue = dq.back().first;
                dq.pop_back();
                if (!dq.empty())
                    dq.back() = make_pair(dq.back().first + lastValue, i) ;
            }
            if (sum <= 0) {
                dq.clear();
                sum = 0;
                l = i+1;
            }
            while (!dq.empty() && sum-dq.front().first >= k) {
                int prevValue = dq.front().first;
                int index = dq.front().second;
                dq.pop_front();
                sum -= prevValue;
                l = index + 1;
            }
            if (sum >= k) {
                ans = min(ans, i - l + 1);
            }
        }
        return (ans == INT_MAX) ? -1 : ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    Solution sol;
    cout << sol.shortestSubarray(arr, k) << endl;
    return 0;
}