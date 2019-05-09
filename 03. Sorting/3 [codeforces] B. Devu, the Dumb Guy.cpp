// Problem: B. Devu, the Dumb Guy
// Link: http://codeforces.com/problemset/problem/439/B
// Solution: Mai Thanh Hiep

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 100000
long long arr[MAX];

int main() {
    long long n, x;
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sort(arr, arr + n);

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += arr[i] * x;
        x--;
        if (x <= 0)
            x = 1;
    }

    cout << ans << endl;

    return 0;
}
