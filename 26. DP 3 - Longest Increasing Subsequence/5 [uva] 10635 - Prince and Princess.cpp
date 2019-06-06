// Problem: 10635 - Prince and Princess
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1576
// Author: Mai Thanh Hiep
// Complexity: T * O(min(qlogp, plogq)); T <= 10; p, q <= n^2; n <= 250

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAX 62501
int dpIncreasing[MAX];
int path[MAX];

// first element greater or equal than x
int lowerBound(const vector<int>& arr, const vector<int>& indices, int left, int right, int x) {
    int pos = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int index = indices[mid];
        if (arr[index] >= x) {
            pos = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return pos;
}

// O(NlogN)
int longestIncreasingSubsequenceBinarySearch(const vector<int>& arr, int n, int* dp, int* path, vector<int>& result) {
    int length = 1;
    for (int i = 0; i < n; i++)
        path[i] = -1;

    result.clear();
    result.push_back(0);

    for (int i = 0; i < n; i++)
        dp[i] = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[result[length - 1]]) {  // insert to result
            path[i] = result[length - 1];
            dp[i] = dp[result[length - 1]] + 1;
            result.push_back(i);
            length++;
        } else { // make arr[result[pos]] as min as possible
            int pos = lowerBound(arr, result, 0, length - 1, arr[i]);
            if (pos > 0) {
                dp[i] = dp[result[pos - 1]] + 1;
                path[i] = result[pos - 1];
            }
            result[pos] = i;
        }
    }

    return dp[result[length - 1]];
}

int main() {
    int t, n, p, q, x;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        cin >> n >> p >> q;
        vector<int> pos(n * n + 1, -1);

        for (int i = 0; i <= p; i++) {
            cin >> x;
            pos[x] = i;
        }

        vector<int> arr;
        for (int i = 0; i <= q; i++) {
            cin >> x;
            if (pos[x] != -1) {
                arr.push_back(pos[x]);
            }
        }

        // find longest increasing subsequence
        vector<int> result;
        int ans = longestIncreasingSubsequenceBinarySearch(arr, arr.size(), dpIncreasing, path, result);

        cout << "Case " << tc << ": " << ans << endl;
    }

    return 0;
}