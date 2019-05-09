// Problem: A. Vitaly and Strings
// Link: http://codeforces.com/problemset/problem/518/A
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string.h>
using namespace std;

// Just like adding 2 number, base=26
char* increaseString(char* s, int offset) {
    int remain = offset;
    int i = strlen(s) - 1;
    int base = 'z' - 'a' + 1;
    int sum;
    while (remain > 0 && i >= 0) {
        sum = s[i] - 'a' + remain;
        s[i] = sum % base + 'a';
        remain = sum / base;
        i--;
    }
}

bool isEqual(char* s1, char* s2) {
    int n = strlen(s1);
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i])
            return false;
    }
    return true;
}

#define MAX 101
int main() {
    char s[MAX], t[MAX];
    scanf("%s %s", s, t);

    // Crease string by one
    increaseString(s, 1);

    // After increase by one, if s equal t => No such string lexicographically larger than s and lexicographically smaller than t, else s is result
    if (isEqual(s, t)) {
        printf("No such string");
    } else {
        printf(s);
    }

    return 0;
}
