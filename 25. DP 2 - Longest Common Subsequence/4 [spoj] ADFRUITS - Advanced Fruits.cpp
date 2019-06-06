// Problem: ADFRUITS - Advanced Fruits
// Link: https://www.spoj.com/problems/ADFRUITS/
// Author: Mai Thanh Hiep
// Complexity: T * O(|str1| * |str2|); |str1|, |str2| <= 100

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAX 100 // All names have a maximum length of 100
int dp[MAX + 1][MAX + 1];
// O(N1 * N2)
int longestCommonSubsequence(string& arr1, int n1, string& arr2, int n2) {
    for (int i = 0; i <= n1; i++) {
        for (int j = 0; j <= n2; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (arr1[i - 1] == arr2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n1][n2];
}

string getLongestCommonSubsequence(string& arr1, int n1, string& arr2, int n2) {
    int len = longestCommonSubsequence(arr1, n1, arr2, n2);
    string result(len, ' ');
    int i = n1, j = n2;
    while (i > 0 && j > 0) {
        if (arr1[i - 1] == arr2[j - 1]) {
            result[--len] = arr1[i - 1];
            i--, j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    return result;
}

int main() {
    string str1, str2;
    while (cin >> str1 >> str2) {
        int len1 = str1.size();
        int len2 = str2.size();
        longestCommonSubsequence(str1, len1, str2, len2); // O(|str1| * |str2|); |str1|, |str2| <= 100 -> This is complexity of this solution
        string lcs = getLongestCommonSubsequence(str1, len1, str2, len2);

        int i = 0, j = 0;
        for (int k = 0; k < lcs.size(); k++) {
            while (str1[i] != lcs[k]) {
                cout << str1[i];
                i++;
            }

            while (str2[j] != lcs[k]) {
                cout << str2[j];
                j++;
            }

            cout << lcs[k];
            i++, j++;
        }

        while (i < len1)
            cout << str1[i++];
        while (j < len2)
            cout << str2[j++];
        cout << endl;
    }

    return 0;
}