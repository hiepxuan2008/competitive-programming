// Problem: MAKEMAZE - VALIDATE THE MAZE
// Link: https://www.spoj.com/problems/MAKEMAZE/
// Solution: Mai Thanh Hiep
// Complexity: M*N

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;
#define MAX 20
struct Point{
    int r;
    int c;

    Point(int _x, int _y) : r(_x), c(_y) {}
    Point() : r(0), c(0) {}
};

char matrix[MAX][MAX];
bool visited[MAX][MAX];
int m, n;
int dX[] = {0, 1, 0, -1};
int dY[] = {-1, 0, 1, 0};

void BFS(const Point& startPoint) {
    memset(visited, 0, sizeof(visited));

    queue<Point> q;
    q.push(startPoint);
    visited[startPoint.r][startPoint.c] = true;

    Point u, v;
    while (!q.empty()) {
        u = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            v.r = u.r + dY[i];
            v.c = u.c + dX[i];

            if (v.r >= 0 && v.r < m && v.c >= 0 && v.c < n && matrix[v.r][v.c] == '.'
                && !visited[v.r][v.c]) {
                visited[v.r][v.c] = true;
                q.push(v);
            }
        }
    }
}

bool isValidMaze() {
    vector<Point> openPoints;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == '.' && (i == 0 || i == m - 1 || j == 0 || j == n - 1))
                openPoints.push_back(Point(i, j));
        }
    }

    // Valid maze have exactly 1 entry point and 1 exit point
    if (openPoints.size() != 2)
        return false;

    Point startPoint = openPoints[0];
    Point endPoint = openPoints[1];
    BFS(startPoint);

    // If endPoint is visited then maze is valid
    return visited[endPoint.r][endPoint.c];
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &m, &n);

        char endline;
        for (int i = 0; i < m; i++) {
            scanf("%c", &endline); // ignore end line char
            for (int j = 0; j < n; j++) {
                scanf("%c", &matrix[i][j]);
            }
        }

        printf(isValidMaze() ? "valid\n" : "invalid\n");
    }

    return 0;
}
