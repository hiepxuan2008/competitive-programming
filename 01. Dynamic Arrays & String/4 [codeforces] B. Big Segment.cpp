// Problem: B. Big Segment
// Link: http://codeforces.com/problemset/problem/242/B
// Solution: Mai Thanh Hiep

#include <iostream>
using namespace std;

#define MAX 100000
#define MAX_POS 1000000000
#define MIN_POS 1

int segments[MAX][2];
int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &segments[i][0], &segments[i][1]);
    }

    int leftMost = MAX_POS;
    int rightMost = MIN_POS;
    for (int i = 0; i < n; i++) {
        leftMost = min(leftMost, segments[i][0]);
        rightMost = max(rightMost, segments[i][1]);
    }

    int ans = -1;
    for (int i = 0; i < n; i++) {
        if (segments[i][0] == leftMost && segments[i][1] == rightMost) {
            ans = i + 1; // Found this segment that cover all other segments
            break;
        }
    }
    printf("%d\n", ans);

    return 0;
}
