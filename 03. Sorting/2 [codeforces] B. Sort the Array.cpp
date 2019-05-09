// Problem: B. Sort the Array
// Link: http://codeforces.com/problemset/problem/451/B
// Solution: Mai Thanh Hiep

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 100000
int A[MAX];
int B[MAX];

bool isEqual(int* arr1, int* arr2, int n) {
    for (int i = 0; i < n; i++)
        if (arr1[i] != arr2[i])
            return false;

    return true;
}

void reverseArr(int* arr, int n) {
    for (int i = 0; i < n/2; i++)
        swap(arr[i], arr[n - i - 1]);
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        B[i] = A[i];
    }

    sort(B, B + n);

    int l = 0;
    while (A[l] == B[l])
        l++;

    int r = n - 1;
    while (A[r] == B[r])
        r--;

    if (l > r) {
        printf("yes\n1 1\n"); // already sort
    } else {
        reverseArr(A + l, r - l + 1);

        if (isEqual(A, B, n))
            printf("yes\n%d %d\n", l+1, r+1);
        else
            printf("no\n");
    }

    return 0;
}