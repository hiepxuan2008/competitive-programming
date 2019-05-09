// Problem: A. Business trip
// Link: https://codeforces.com/problemset/problem/149/A
// Solution: Mai Thanh Hiep

#include <iostream>
#include <algorithm>
using namespace std;

int arr[12];

int main() {
    int k;
    scanf("%d", &k);
    for (int i = 0; i < 12; i++) {
        scanf("%d", &arr[i]);
    }

    if (k == 0) {
        printf("0\n"); // No need to water anymore
    } else {
        // Sort in non-increasing
        sort(arr, arr + 12, greater<int>());

        int grow = 0;
        int i = 0;
        while (grow - k < 0 && i < 12) {
            grow += arr[i];
            i++;
        }

        printf("%d\n", grow >= k ? i : -1);
    }

    return 0;
}
