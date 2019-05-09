// Problem: A. Chores
// Link: http://codeforces.com/problemset/problem/169/A
// Solution: Mai Thanh Hiep

#include <iostream>
#include <algorithm>

using namespace std;

#define MAX 2000
int h[MAX];
int main()
{
    int n, a, b;
    cin >> n >> a >> b;

    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    sort(h, h + n);

    int ans = h[b] - h[b - 1];

    cout << ans << endl;

    return 0;
}