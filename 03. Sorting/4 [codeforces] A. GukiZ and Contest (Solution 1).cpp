// Problem: A. GukiZ and Contest
// Link: https://codeforces.com/problemset/problem/551/A
// Solution: Mai Thanh Hiep
// Complexibility: O(n^2)

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 2000
int arr[MAX];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        count = 0;
        for (int j = 0; j < n; j++)
            if (arr[j] > arr[i])
                count++;

        cout << count + 1 << " ";
    }

    return 0;
}
