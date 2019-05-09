// Problem: B. Semifinals
// Link: https://codeforces.com/problemset/problem/378/B
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string.h>
using namespace std;

#define MAX 100000
int a[MAX], b[MAX];
char str1[MAX + 1], str2[MAX + 1];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }

    // Default: string with 0 characters
    for (int i = 0; i < n; i++) {
        str1[i] = str2[i] = '0';
    }
    str1[n] = str2[n] = 0; // end of string

    // Case k = 0: Pick n top best results
    int i = 0, j = 0;
    for (int k = 0; k < n; k++) {
        if (a[i] < b[j]) {
            str1[i++] = '1';
        } else {
            str2[j++] = '1';
        }
    }

    // Case k = n/2: Pick top n/2 participants per semifinal
    for (int i = 0; i < n/2; i++) {
        str1[i] = str2[i] = '1';
    }

    printf("%s\n%s\n", str1, str2);

    return 0;
}
