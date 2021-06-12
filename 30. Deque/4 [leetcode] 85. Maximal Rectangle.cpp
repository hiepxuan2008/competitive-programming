// Problem: 85. Maximal Rectangle
// Link: https://leetcode.com/problems/maximal-rectangle/ or https://oj.vnoi.info/problem/qbrect
// Author: Mai Thanh Hiep
// Complexity: O(M * N), where M is number of rows, N is number of columns in the matrix

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

#define MAXN 1010
#define MAXM 1010

int arr[MAXM][MAXN];

int findMaxAreaInHistory(const vector<int>& heights) {
    stack<int> st;
    st.push(-1);
    int n = heights.size();
    int maxArea = 0;
    for (int i = 0; i < n; ++i) {
        while (st.top() != -1 && heights[st.top()] >= heights[i]) {
            int currentHeight = heights[st.top()];
            st.pop();
            int currentWidth = i - st.top() - 1;
            maxArea = max(maxArea, currentWidth * currentHeight);
        }
        st.push(i);
    }
    while (st.top() != -1) {
        int currentHeight = heights[st.top()];
        st.pop();
        int currentWidth = n - st.top() - 1;
        maxArea = max(maxArea, currentWidth * currentHeight);
    }
    return maxArea;
}

int solve(int m, int n) {
    vector<int> heights(n);
    int maxArea = 0;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (r == 0)
                heights[c] = arr[r][c];
            else if (arr[r][c] == 0)
                heights[c] = 0;
            else
                heights[c] += 1;
        }
        maxArea = max(maxArea, findMaxAreaInHistory(heights));
    }
    return maxArea;
}

int main() {
    ios_base::sync_with_stdio(false);

    int m, n;
    cin >> m >> n;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            cin >> arr[r][c];
        }
    }
    cout << solve(m, n) << endl;
    return 0;
}