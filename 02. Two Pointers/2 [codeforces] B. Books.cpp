// Problem: B. Books
// Link: https://codeforces.com/problemset/problem/279/B
// Solution: Mai Thanh Hiep

#include <iostream>

using namespace std;

#define MAX 100000
int arr[MAX];
int main()
{
    int n, t;
    cin >> n >> t;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int sum = 0;
    int ans = 0;
    int l, r;
    l = r = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        if (sum <= t) {
            r = i; // update new right bound
            ans = max(r-l+1, ans);
        } else {
            sum -= arr[l];
            l++; // update new left bound
        }
    }

    cout << ans << endl;

    return 0;
}
