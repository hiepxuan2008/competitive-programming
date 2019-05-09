// Problem: EKO - Eko
// Link: https://www.spoj.com/problems/EKO/
// Solution: Mai Thanh Hiep
// Complexity: O(N * Log(max(hi)))

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 1000000

long long getCutWoodAmount(vector<int>& arr, int h) {
    long long cutWoodAmount = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > h)
            cutWoodAmount += (long long) (arr[i] - h);
    }
    return cutWoodAmount;
}

int solve(vector<int>& arr, int left, int right, int expectAmount) {
    int n = arr.size();
    int mid;
    int height = -1;
	while (left <= right) {
        mid = left + (right-left) / 2;
        long long cutWoodAmount = getCutWoodAmount(arr, mid);

        if (cutWoodAmount >= expectAmount) {
            height = mid; // the higher height the better
            left = mid + 1; // continue search on [mid+1, right]
        } else {
            right = mid - 1; // search on [left, mid - 1]
        }
	}
	return height;
}

int main() {
	int n, m;
	cin >> n >> m;

	int highestTree = 0;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
        highestTree = max(highestTree, arr[i]);
	}

    cout << solve(arr, 0, highestTree, m) << endl;

	return 0;
}
