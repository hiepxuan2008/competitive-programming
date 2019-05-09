// Problem: B. Pasha and Tea
// Link: https://codeforces.com/problemset/problem/557/B
// Solution: Mai Thanh Hiep

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 200000
int arr[MAX];

int main() {
    int n, w;
    scanf("%d %d", &n, &w);
    for (int i = 0; i < n * 2; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort in non-decreasing by size of cups
    sort(arr, arr + 2 * n);

    // Find maxAmountPerGirlCup
    double smallestGirlCup = arr[0];
    double smallestBoyCup = arr[n];
    double maxAmountPerGirlCup = min(smallestBoyCup / 2.0, smallestGirlCup);

    double ans = min(maxAmountPerGirlCup * 3 * n, (double) w);
    printf("%.7f\n", ans);

    return 0;
}
