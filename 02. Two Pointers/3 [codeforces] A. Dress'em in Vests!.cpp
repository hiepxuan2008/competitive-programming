// Problem: A. Dress'em in Vests!
// Link: https://codeforces.com/problemset/problem/161/A
// Solution: Mai Thanh Hiep

#include <iostream>
#include <vector>

using namespace std;

#define MAX 100000
int A[MAX];
int B[MAX];
int main() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }

    int j = 0;
    vector<pair<int, int>> results;
    for (int i = 0; i < n; i++) {
        // find bulletproof vest that >= A[i]-x
        while (j < m && B[j] < A[i] - x) {
            j++;
        }

        if (j == m) // out of bulletproof vest
            break;

        if (B[j] <= A[i] + y) {
            results.push_back(make_pair(i + 1, j + 1));
            j++; // Next bulletproof vest
        }
    }

    cout << results.size() << endl;
    for (int i = 0; i < results.size(); i++) {
        cout << results[i].first << " " << results[i].second << endl;
    }

    return 0;
}
