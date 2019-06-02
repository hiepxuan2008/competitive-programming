// Problem: 471 D. MUH and Cube Walls
// Link: https://codeforces.com/problemset/problem/471/D
// Author: Mai Thanh Hiep
// Complexity: O(n + w); n, w <= 2 * 10^5

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// O(|p|)
void KMPPreprocess(const vector<int>& p, vector<int>& prefix) {
    prefix[0] = 0;
    int m = prefix.size();
    int j = 0;
    int i = 1;
    while (i < m) {
        if (p[i] == p[j]) {
            j++;
            prefix[i] = j;
            i++;
        } else {
            if (j != 0) {
                j = prefix[j - 1];
            } else {
                prefix[i] = 0;
                i++;
            }
        }
    }
}

// O(|s| + |p|)
int KMPSearchCount(const vector<int>& t, const vector<int>& p, vector<int>& prefix) {
    int n = t.size();
    int m = p.size();
    int i = 0, j = 0;
    int foundCount = 0;
    while (i < n) {
        if (p[j] == t[i]) {
            j++;
            i++;
        }
        if (j == m) {
            foundCount++;
            j = prefix[j - 1];
        } else if (i < n && p[j] != t[i]) {
            if (j != 0) {
                j = prefix[j - 1];
            } else {
                i++;
            }
        }
    }
    return foundCount;
}

int main() {
    int n, w;
    cin >> n >> w;

    vector<int> A(n);
    vector<int> B(w);

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    for (int i = 0; i < n - 1; i++) {
        A[i] = A[i + 1] - A[i];
    }

    for (int i = 0; i < w; i++) {
        cin >> B[i];
    }

    for (int i = 0; i < w - 1; i++) {
        B[i] = B[i + 1] - B[i];
    }
    --n, --w;
    A.resize(n);
    B.resize(w);

    if (w > 0) {
        vector<int> prefix(w);
        KMPPreprocess(B, prefix);
        cout << KMPSearchCount(A, B, prefix) << endl; // O(n + w); n, w <= 2 * 10^5
    } else {
        cout << (n + 1) << endl;
    }

    return 0;
}