// Problem: B. Approximating a Constant Range
// Link: https://codeforces.com/problemset/problem/602/B
// Solution: Mai Thanh Hiep

#include <iostream>
#include <vector>
using namespace std;

#define MAX 100000
int arr[MAX];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int i = 0, j = 0;
    int best = 0;
    int maxIndex = 0, minIndex = 0;
    while (i < n) {
        // maxIndex, minIndex as right side as possible
        if (arr[i] >= arr[maxIndex])
            maxIndex = i;
        if (arr[i] <= arr[minIndex])
            minIndex = i;

        if (arr[maxIndex] - arr[minIndex] > 1) {
            // Find alternative minIndex
            if (arr[maxIndex] == arr[i]) {
                j = ++minIndex;
            }
            // Find alternative maxIndex
            else if (arr[minIndex] == arr[i]) {
                j = ++maxIndex;
            }
        } else {
            best = max(best, i - j + 1);
            i++;
        }
    }

    cout << best << endl;

    return 0;
}
