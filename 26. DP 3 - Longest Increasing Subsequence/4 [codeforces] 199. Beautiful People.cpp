// Problem: 199. Beautiful People
// Link: https://codeforces.com/problemsets/acmsguru/problem/99999/199
// Author: Mai Thanh Hiep
// Complexity: O(NlogN), N <= 100000

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define MAX 100001
int dpIncreasing[MAX];
int path[MAX];

struct Member {
	int strength;
	int beauty;
	int id;
};

// first element greater or equal than x
int lowerBound(const vector<Member>& members, const vector<int>& indices, int left, int right, int x) {
	int pos = -1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		int index = indices[mid];
		if (members[index].beauty >= x) {
			pos = mid;
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return pos;
}

// O(NlogN)
int longestIncreasingSubsequenceBinarySearch(const vector<Member>& members, int n, int* dp, int* path, vector<int>& result) {
	int length = 1;
	for (int i = 0; i < n; i++)
		path[i] = -1;

	result.clear();
	result.push_back(0);

	for (int i = 0; i < n; i++)
		dp[i] = 1;

	for (int i = 1; i < n; i++) {
		if (members[i].beauty > members[result[length - 1]].beauty) {  // insert to result
			path[i] = result[length - 1];
			dp[i] = dp[result[length - 1]] + 1;
			result.push_back(i);
			length++;
		}
		else { // make arr[result[pos]] as min as possible
			int pos = lowerBound(members, result, 0, length - 1, members[i].beauty);
			if (pos > 0) {
				dp[i] = dp[result[pos - 1]] + 1;
				path[i] = result[pos - 1];
			}
			result[pos] = i;
		}
	}

	return dp[result[length - 1]];
}

bool increasingStrengthThenDecreasingBeautyComparator(const Member& a, const Member& b) {
	if (a.strength == b.strength)
		return a.beauty > b.beauty;

	return a.strength < b.strength;
}

void printPath(vector<Member> members, int i) {
	while (i != -1) {
		cout << members[i].id << " ";
		i = path[i];
	}
}

int main() {
	int n;
	cin >> n;

	vector<Member> members(n);

	for (int i = 0; i < n; i++) {
		cin >> members[i].strength >> members[i].beauty;
		members[i].id = (i + 1);
	}

	// sort in increasing of strength, if else strength than sort in descreasing by beauty
	sort(members.begin(), members.end(), increasingStrengthThenDecreasingBeautyComparator);

	// find longest increasing subsequence
	vector<int> result;
	cout << longestIncreasingSubsequenceBinarySearch(members, n, dpIncreasing, path, result) << endl;
	printPath(members, result[result.size() - 1]);

	return 0;
}