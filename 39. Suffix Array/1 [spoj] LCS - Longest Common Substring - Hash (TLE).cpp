// Problem: LCS - Longest Common Substring
// Link: https://www.spoj.com/problems/LCS/
// Author: Mai Thanh Hiep
// Complexity: O((M+N) * logN), where M <= 250000 is the maximum, N <= 250000 is the minimum between length of str1 and length of str2 corresponding (TLE).

#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

typedef unsigned long long ull;
class Solution {
public:
    int m, n, BASE = 27LL;
    vector<ull> hash1, hash2, POW;
    int findLCCS(const string& str1, const string& str2) {
        m = str1.size(), n = str2.size();
        hash1.assign(m+1, 0);
        hash2.assign(n+1, 0);
        POW.assign(max(m, n) + 1, 1);
        for (int i = 0; i < max(m, n); ++i) POW[i+1] = POW[i] * BASE; // Compute POW of BASE
        for (int i = 0; i < m; ++i) hash1[i+1] = hash1[i] * BASE + str1[i] - 'a' + 1; // Compute hashing values of str1
        for (int i = 0; i < n; ++i) hash2[i+1] = hash2[i] * BASE + str2[i] - 'a' + 1; // Compute hashing values of str2

        int left = 1, right = min(m, n), ans = 0;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (foundSubString(str1, str2, mid)) {
                ans = mid;
                left = mid + 1; // Try to expand size
            } else right = mid - 1; // Try to shrink size
        }
        return ans;
    }
    ull getHash(const vector<ull>& hash, int left, int right) { // 0-based indexing, right inclusive
        return hash[right+1] - hash[left] * POW[right - left + 1];
    }
    bool foundSubString(const string& nums1, const string& nums2, int size) {
        unordered_map<ull, vector<int>> seen;
        for (int i = 0; i < m-size+1; ++i) {
            ull h = getHash(hash1, i, i + size - 1);
            seen[h].push_back(i);
        }
        for (int i = 0; i < n-size+1; ++i) {
            ull h = getHash(hash2, i, i + size - 1);
            if (!seen.count(h)) continue;
            for (int j : seen[h]) // Double check - This rarely happens when collision occurs -> No change in time complexity
                if (equal(nums1.begin()+j, nums1.begin()+j+size, nums2.begin()+i, nums2.begin()+i+size))
                    return true;
        }
        return false;
    }
};

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str1, str2;
    cin >> str1 >> str2;

    cout << Solution().findLCCS(str1, str2) << '\n';

    return 0;
}