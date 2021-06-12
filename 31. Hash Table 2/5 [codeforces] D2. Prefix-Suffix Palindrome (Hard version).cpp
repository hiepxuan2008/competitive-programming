// Problem: D2. Prefix-Suffix Palindrome (Hard version)
// Link: https://codeforces.com/problemset/problem/1326/D2
// Author: Mai Thanh Hiep
// Complexity: O(S), where S <= 10^6 is the sum of lengths of strings over all test cases

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <climits>
#include <queue>
#include <set>
#include <unordered_set>

using namespace std;

typedef long long ll;
const int MAXN = 1e6 + 5;
const ll BASE = 27;
ll POW[MAXN];

string subString(const string& str, int left, int right) { // left inclusive, right exclusive
    return str.substr(left, right - left);
}

bool isPalindrome(const string& str) {
    int left = 0, right = (int)str.size() - 1;
    while (left <= right && str[left] == str[right]) {
        left += 1;
        right -= 1;
    }
    return left > right;
}

int getLongestPalindromeSubString(const string& str) {
    ll hash = 0, hashReversed = 0;
    int n = str.size();
    POW[0] = 1;
    vector<int> possibleLen;
    for (int i = 0; i < n; ++i) {
        hash = hash * BASE + str[i] - 'a' + 1;
        hashReversed = hashReversed + (str[i] - 'a' + 1) * POW[i];
        POW[i + 1] = POW[i] * BASE;
        if (hash == hashReversed) {
            possibleLen.push_back(i + 1);
        }
    }
    // double check to avoid case hash collision -> exit early -> don't change time complexity
    for (auto it = possibleLen.rbegin(); it != possibleLen.rend(); ++it) {
        if (isPalindrome(subString(str, 0, *it))) return *it;
    }
    return 0;
}

string solve(const string& str) {
    int n = str.size();
    int left = 0, right = n -1 ;
    while (left <= right && str[left] == str[right]) {
        left += 1;
        right -= 1;
    }
    if (left > right) return str;
    // now str[left] != str[right]
    string midSubStr = subString(str, left, right+1);
    string midSubStrReversed = midSubStr;
    reverse(midSubStrReversed.begin(), midSubStrReversed.end());

    int longestFromLeft = getLongestPalindromeSubString(midSubStr);
    int longestFromRight = getLongestPalindromeSubString(midSubStrReversed);

    string mid = "";
    if (longestFromLeft >= longestFromRight) {
        mid = subString(midSubStr, 0, longestFromLeft); // take palindrome string from left side
    } else {
        mid = subString(midSubStrReversed, 0, longestFromRight); // take palindrome string from right side
    }
    return subString(str, 0, left) + mid + subString(str, right+1, n);
}

int main() {
    ios_base::sync_with_stdio(false);
    
    string str;
    int t;
    cin >> t;
    while (t-- > 0) {
        cin >> str;
        cout << solve(str) << endl;
    }
    return 0;
}