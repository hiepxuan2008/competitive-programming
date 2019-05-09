// Problem: A. GukiZ and Contest
// Link: https://codeforces.com/problemset/problem/551/A
// Solution: Mai Thanh Hiep
// Complexity: O(NLogN)

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 2000
typedef pair<int, int> pp;
pp arr[MAX];
int ranking[MAX];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first; // score
        arr[i].second = i; // id
    }

	// sort in non-increasing by score
    sort(arr, arr + n, greater<pp>());

    int currentScore = -1;
    int currentRank;
    for (int i = 0; i < n; i++) {
        if (currentScore != arr[i].first) {
            currentRank = i + 1;
            currentScore = arr[i].first;
        }

        ranking[arr[i].second] = currentRank;
    }

    for (int i = 0; i < n; i++) {
        cout << ranking[i] << " ";
    }

    return 0;
}
