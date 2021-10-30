// Problem: LCS - Longest Common Substring
// Link: https://www.spoj.com/problems/LCS/
// Author: Mai Thanh Hiep
// Complexity: O((M+N) * log(M+N)), where M <= 250000 is the length of str1, N <= 250000 is the length of str2.

#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

const int MAX_DIGIT = 256;

void countingSort(vector<int>& SA, vector<int>& RA, int k = 0) {
    int n = SA.size();
    vector<int> cnt(max(MAX_DIGIT, n));
    for (int i = 0; i < n; ++i) {
        if (i + k < n)
            cnt[RA[i+k]]++;
        else
            cnt[0]++;
    }
    for (int i = 1; i < cnt.size(); ++i)
        cnt[i] += cnt[i-1];

    vector<int> tempSA(n);
    for (int i = n - 1; i >= 0; --i) {
        if (SA[i] + k < n)
            tempSA[--cnt[RA[SA[i] + k]]] = SA[i];
        else
            tempSA[--cnt[0]] = SA[i];
    }
    SA = tempSA;
}

// Time complexity: O(NlogN)
vector<int> constructSA(const string& s) {
    int n = s.length();
    vector<int> SA(n), RA(n), tempRA(n);
    for (int i = 0; i < n; ++i) {
        RA[i] = s[i];
        SA[i] = i;
    }

    for (int step = 1; step < n; step <<= 1) {
        countingSort(SA, RA, step);
        countingSort(SA, RA, 0);

        tempRA[SA[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i] + step] == RA[SA[i-1] + step]) {
                tempRA[SA[i]] = tempRA[SA[i-1]];
            } else {
                tempRA[SA[i]] = tempRA[SA[i-1]] + 1;
            }
        }
        RA = tempRA;
        if (RA[SA[n-1]] == n-1) break;
    }
    return SA;
}

// Kasai's Algorithm
// Time complexity: O(N)
vector<int> computeLCP(const string& s, const vector<int>& SA) {
    int n = SA.size();
    vector<int> LCP(n); // Longest Common Prefix
    vector<int> PLCP(n); // Permuted Longest Common Prefix
    vector<int> c(n, 0);
    for (int i = 0; i < n; ++i)
        c[SA[i]] = i;
    int k = 0;
    for (int i = 0; i < n - 1; ++i) {
        int j = SA[c[i] - 1];
        k = max(k - 1, 0);
        while (s[i+k] == s[j+k]) ++k;
        PLCP[i] = k;
    }
    for (int i = 0; i < n; ++i)
        LCP[i] = PLCP[SA[i]];

    return LCP;
}

int solve(const string& str1, const string& str2) {
    string s = str1 + "#" + str2 + "$";
    vector<int> SA = constructSA(s);
    vector<int> LCP = computeLCP(s, SA);
    int ans = 0;
    for (int i = 1; i < s.size(); ++i) {
        if (SA[i-1] < str1.size() && SA[i] > str1.size() || SA[i] < str1.size() && SA[i-1] > str1.size()) {
            ans = max(ans, LCP[i]);
        }
    }
    return ans;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str1, str2;
    cin >> str1 >> str2;

    cout << solve(str1, str2) << '\n';

    return 0;
}