// Problem: B. George and Round
// Link: https://codeforces.com/problemset/problem/387/B
// Solution: Mai Thanh Hiep

#include <iostream>

using namespace std;

#define MAX 3000
int A[MAX];
int B[MAX];
int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }

    int j = 0;
    int feed = 0;
    for (int i = 0; i < n; i++) {
        while (j < m && B[j] < A[i])
            j++;

        if (j < m) {
            feed++; // feed prepare problems
            j++; // next prepare
        } else {
            break;
        }
    }

    cout << n - feed << endl;

    return 0;
}
