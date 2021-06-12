// Problem: PLSQUARE - Palin Square
// Link: https://www.spoj.com/problems/PLSQUARE/
// Author: Mai Thanh Hiep
// Complexity: O(N^3), where N <= 200 is size of the board

#include <iostream>
#include <algorithm>

using namespace std;
#define ll long long

const int MAXN = 205;
ll BASE = 27;
int n;
ll hashRow[MAXN][MAXN];
ll hashRowRev[MAXN][MAXN];
ll hashCol[MAXN][MAXN];
ll hashColRev[MAXN][MAXN];
ll POW[MAXN];
string arr[MAXN];
bool f[MAXN][MAXN][MAXN];

ll getHashRow(int row, int col1, int col2) {
    return hashRow[row][col2] - hashRow[row][col1 - 1] * POW[col2 - col1 + 1];
}

ll getHashRowRev(int row, int col1, int col2) {
    return hashRowRev[row][col1] - hashRowRev[row][col2 + 1] * POW[col2 - col1 + 1];
}

ll getHashCol(int col, int row1, int row2) {
    return hashCol[row2][col] - hashCol[row1 - 1][col] * POW[row2 - row1 + 1];
}

ll getHashColRev(int col, int row1, int row2) {
    return hashColRev[row1][col] - hashColRev[row2 + 1][col] * POW[row2 - row1 + 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    POW[0] = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        arr[i] = " " + arr[i]; // One-based indexing
        POW[i] = POW[i - 1] * BASE;
    }

    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            hashRow[r][c] = hashRow[r][c - 1] * BASE + arr[r][c] - 'a' + 1;
            hashCol[r][c] = hashCol[r - 1][c] * BASE + arr[r][c] - 'a' + 1;
        }
    }

    for (int r = n; r >= 1; --r) {
        for (int c = n; c >= 1; --c) {
            hashRowRev[r][c] = hashRowRev[r][c + 1] * BASE + arr[r][c] - 'a' + 1;
            hashColRev[r][c] = hashColRev[r + 1][c] * BASE + arr[r][c] - 'a' + 1;
        }
    }

    // All squares of size k = 0 or k == 1 are valid Palin Square
    for (int k = 0; k <= 1; ++k)
        for (int r = 1; r <= n; ++r)
            for (int c = 1; c <= n; ++c)
                f[r][c][k] = true;

    int ans = 1;
    for (int k = 2; k <= n; ++k) {
        for (int r = 1; r <= n - k + 1; ++r) {
            for (int c = 1; c <= n - k + 1; ++c) {
                int er = r + k - 1; // end row
                int ec = c + k - 1; // end column
                ll top = getHashRow(r, c, ec);
                ll topRev = getHashRowRev(r, c, ec);
                ll bot = getHashRow(er, c, ec);
                ll left = getHashCol(c, r, er);
                ll leftRev = getHashColRev(c, r, er);
                ll right = getHashCol(ec, r, er);
                if (top == topRev && top == bot && left == leftRev && left == right && f[r + 1][c + 1][k - 2]) {
                    f[r][c][k] = true;
                    ans = max(ans, k);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}