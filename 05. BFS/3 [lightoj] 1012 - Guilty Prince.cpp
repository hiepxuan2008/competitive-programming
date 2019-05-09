// Problem: 1012 - Guilty Prince
// Link: http://lightoj.com/volume_showproblem.php?problem=1012
// Solution: Mai Thanh Hiep
// Complexity: W*H

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;
#define MAX 20
struct Point{
    int r;
    int c;

    Point(int _r, int _c) : r(_r), c(_c) {}
    Point() : r(0), c(0) {}
};

char matrix[MAX][MAX];
bool visited[MAX][MAX];
int H, W;
int dX[] = {0, 1, 0, -1};
int dY[] = {-1, 0, 1, 0};

int BFS(const Point& startPoint) {
    memset(visited, 0, sizeof(visited));

    queue<Point> q;
    q.push(startPoint);
    visited[startPoint.r][startPoint.c] = true;
    int count = 1;

    Point u, v;
    while (!q.empty()) {
        u = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            v.r = u.r + dY[i];
            v.c = u.c + dX[i];

            if (v.r >= 0 && v.r < H && v.c >= 0 && v.c < W && matrix[v.r][v.c] == '.'
                && !visited[v.r][v.c]) {
                visited[v.r][v.c] = true;
                count++;
                q.push(v);
            }
        }
    }

    return count;
}

int solve() {
    Point startPoint;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (matrix[i][j] == '@') {
                startPoint.r = i;
                startPoint.c = j;
                break;
            }
        }
    }

    return BFS(startPoint);
}

int main() {
    int t;
    scanf("%d", &t);

    for (int c = 1; c <= t; c++) {
        scanf("%d %d", &W, &H);

        char endline;
        for (int i = 0; i < H; i++) {
            scanf("%c", &endline); // ignore end line char
            for (int j = 0; j < W; j++) {
                scanf("%c", &matrix[i][j]);
            }
        }

        printf("Case %d: %d\n", c, solve());
    }

    return 0;
}
