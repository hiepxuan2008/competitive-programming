// Problem: 531 - Compromise
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=472
// Author: Mai Thanh Hiep
// Complexity: T * O(LENGTH_OF_WORD * N^2); N <= 100, LENGTH_OF_WORD <= 30

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAXW 100 // Both texts will contain less than 100 words
int dp[MAXW + 1][MAXW + 1];
// O(N1 * N2)
int longestCommonSubsequence(vector<string>& arr1, int n1, vector<string>& arr2, int n2) {
	for (int i = 0; i <= n1; i++) {
		for (int j = 0; j <= n2; j++) {
			if (i == 0 || j == 0)
				dp[i][j] = 0;
			else if (arr1[i - 1] == arr2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	return dp[n1][n2];
}

vector<string> getLongestCommonSubsequenceWords(vector<string>& arr1, int n1, vector<string>& arr2, int n2) {
	int len = longestCommonSubsequence(arr1, n1, arr2, n2);
	vector<string> result(len);
	int i = n1, j = n2;
	while (i > 0 && j > 0) {
		if (arr1[i - 1] == arr2[j - 1]) {
			result[--len] = arr1[i - 1];
			i--, j--;
		}
		else if (dp[i - 1][j] > dp[i][j - 1]) {
			i--;
		}
		else {
			j--;
		}
	}
	return result;
}

void splitString(const string& str, vector<string>& words) {
	string temp = "";
	for (int i = 0; i < str.size(); i++) {
		if (str[i] != ' ') {
			temp += str[i];
		}
		else if (temp.size() > 0) {
			words.push_back(temp);
			temp = "";
		}
	}
	if (temp.size() > 0) {
		words.push_back(temp);
	}
}

int main() {
	string str1, str2, temp;
	vector<string> words1, words2;
	while (getline(cin, temp)) {
		str1 = "";

		while (temp != "#") {
			str1 += temp + " ";
			getline(cin, temp);
		}
		words1.clear();
		splitString(str1, words1);

		str2 = "";
		while (getline(cin, temp) && temp != "#") {
			str2 += temp + " ";
		}
		words2.clear();
		splitString(str2, words2);

		vector<string> result = getLongestCommonSubsequenceWords(words1, words1.size(), words2, words2.size());
		int n = result.size();
		for (int i = 0; i < n - 1; i++) {
			cout << result[i] << " ";
		}
		cout << result[n - 1] << endl;
	}

	return 0;
}