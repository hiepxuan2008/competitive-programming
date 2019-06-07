// Problem: 448 C. Painting Fence
// Link: https://codeforces.com/problemset/problem/448/C
// Author: Mai Thanh Hiep
// Complexity: O(NLogN), N <= 5000

#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 5000
int arr[MAXN], n;

int solve(int l, int r) {
    if (l > r)
        return 0;

    int minElement = min_element(arr + l, arr + 1 + r) - arr;
    int minHeight = arr[minElement];
    int len = r - l + 1;

    if (minHeight >= len) {
        // It's better to paint verticle each planks
        for (int i = l; i <= r; i++)
            arr[i] = 0;
        return len;
    } else {
        // Try to paint horizontal minHeight strokes from the bottom of each planks
        for (int i = l; i <= r; i++)
            arr[i] -= minHeight;

        int leftStrokes = solve(l, minElement - 1);
        int rightStrokes = solve(minElement + 1, r);

        return min(len, minHeight + leftStrokes + rightStrokes);
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int ans = solve(0, n - 1);
    cout << ans << endl;

    return 0;
}