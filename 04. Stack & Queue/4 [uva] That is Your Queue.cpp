// Problem: 12207 - That is Your Queue
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3359
// Solution: Mai Thanh Hiep
// Complexity: O(N^2), N max = 1000

#include <iostream>
#include <queue>
using namespace std;

int main() {
    int P, C;
    int t = 0;
    while (true) {
        scanf("%d %d", &P, &C);
        if (P == 0)
            break;

        printf("Case %d:\n", ++t);

        queue<int> q1, q2;
        for (int i = 0; i < min(P, C); i++) {
            q1.push(i + 1);
        }

        char c;
        int top;
        int x;
        for (int i = 0; i < C; i++) {
            scanf("%c %c", &c, &c); // discard first \n char
            if (c == 'N') {
                top = q1.front();
                printf("%d\n", top);
                q1.pop();
                q1.push(top);
            } else if (c == 'E') {
                scanf("%d", &x);

                q2.push(x);
                while (!q1.empty()) {
                    if (q1.front() != x) {
                        q2.push(q1.front());
                    }
                    q1.pop();
                }

                q1.swap(q2);
            }
        }
    }

	return 0;
}
