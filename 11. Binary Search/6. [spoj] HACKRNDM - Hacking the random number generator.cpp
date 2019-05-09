// Problem: HACKRNDM - Hacking the random number generator
// Link: https://www.spoj.com/problems/HACKRNDM/
// Solution: Mai Thanh Hiep
// Complexity: O(NlogN)

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 100000
int arr[MAX];

int binarySearch(int* arr, int l, int r, int x) {
    int m;
    while (l <= r) {
        m = (l + r) / 2;
        if (arr[m] == x)
            return m;
        else if (arr[m] < x) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return -1;
}

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sort(arr, arr + n);

    int countPairs = 0;
    for (int i = 0; i < n; i++) {
        if (binarySearch(arr, i + 1, n, arr[i] + k) != -1) {
            countPairs++;
        }
    }

    cout << countPairs << endl;

	return 0;
}
