// Problem: 10474 - Where is the Marble?
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1415
// Author: Mai Thanh Hiep

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 10000
int arr[MAX];

int main() {
    int n, q;
    int c = 0;
    while (true) {
        cin >> n >> q;
        if (n == 0)
            break;

        cout << "CASE# " << (++c) << ":" << endl;

        for (int i = 0; i < n; i++)
            cin >> arr[i];

        sort(arr, arr + n);

        int x;
        for (int i = 0; i < q; i++) {
            cin >> x;
            int index = lower_bound(arr, arr + n, x) - arr;
            if (index < n && arr[index] == x) {
                cout << x << " found at " << index + 1 << endl;
            } else {
                cout << x << " not found" << endl;
            }
        }
    }

    return 0;
}
