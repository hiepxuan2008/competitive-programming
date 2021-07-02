// Problem: 11019 - Matrix Matcher
// Link: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1960
// Author: Mai Thanh Hiep
// Complexity: O(nMatrixRows * nMatrixCols + nPatternRows * nPatternCols), where nMatrixRows, nMatrixCols <= 1000; nPatternRows, nPatternCols <= 100

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAX_MATRIX_ROWS = 1005;
const int MAX_MATRIX_COLS = 1005;
const int MAX_PATTERN_ROWS = 105;
const int MAX_PATTERN_COLS = 105;
string matrix[MAX_MATRIX_ROWS];
string pattern[MAX_PATTERN_ROWS];
ll hashByCols[MAX_MATRIX_COLS][MAX_MATRIX_ROWS];
ll POW[MAX_MATRIX_COLS];
ll BASE = 27;

vector<int> computeKMP(vector<ll>& P) {
    int m = P.size();
    vector<int> lps(m);
    int j = 0;
    for (int i = 1; i < m; ++i) {
        while (j > 0 && P[i] != P[j]) j = lps[j-1];
        if (P[i] == P[j]) lps[i] = ++j;
    }
    return lps;
}

ll getHash(int c, int start, int end) { // start, end inclusive; zero-based indexing
    return hashByCols[c][end + 1] - hashByCols[c][start] * POW[end - start + 1];
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, nMatrixRows, nMatrixCols, nPatternRows, nPatternCols;
    cin >> t;

    POW[0] = 1LL;
    for (int i = 1; i < MAX_MATRIX_ROWS; ++i) POW[i] = POW[i - 1] * BASE;

    while (t--) {
        cin >> nMatrixRows >> nMatrixCols;
        for (int i = 0; i < nMatrixRows; ++i) cin >> matrix[i];
        cin >> nPatternRows >> nPatternCols;
        for (int i = 0; i < nPatternRows; ++i) cin >> pattern[i];

        for (int c = 0; c < nMatrixCols; ++c) {
            hashByCols[c][0] = 0LL;
            for (int r = 0; r < nMatrixRows; ++r) {
                hashByCols[c][r+1] = hashByCols[c][r] * BASE + matrix[r][c] - 'a' + 1;
            }
        }
        vector<ll> patternHash(nPatternCols);
        for (int c = 0; c < nPatternCols; ++c) { // O(nPatternRows * nPatternCols)
            patternHash[c] = 0LL;
            for (int r = 0; r < nPatternRows; ++r) {
                patternHash[c] = patternHash[c] * BASE + pattern[r][c] - 'a' + 1;
            }
        }
        vector<int> lps = computeKMP(patternHash);
        int ans = 0;
        for (int r = 0; r < nMatrixRows - nPatternRows + 1; ++r) { // O(nMatrixRows * nMatrixCols)
            for (int i = 0, j = 0; i < nMatrixCols; ++i) {
                while (j > 0 && patternHash[j] != getHash(i, r, r + nPatternRows - 1)) j = lps[j - 1];
                if (patternHash[j] == getHash(i, r, r + nPatternRows - 1)) ++j;
                if (j == nPatternCols) {
                    ++ans;
                    j = lps[j-1];
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}