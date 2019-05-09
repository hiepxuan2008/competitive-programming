// Problem: UCV2013H - Slick
// Link: https://www.spoj.com/problems/UCV2013H/
// Solution: Mai Thanh Hiep
// Complexity: N*M

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <map>

using namespace std;
#define MAX 250
struct Point{
    int r;
    int c;

    Point(int _x, int _y) : r(_x), c(_y) {}
    Point() : r(0), c(0) {}
};

int matrix[MAX][MAX];
bool visited[MAX][MAX];
int N, M;
int dX[] = {0, 1, 0, -1};
int dY[] = {-1, 0, 1, 0};

int BFS(const Point& startPoint) {
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

            if (v.r >= 0 && v.r < N && v.c >= 0 && v.c < M && matrix[v.r][v.c] == 1
                && !visited[v.r][v.c]) {
                visited[v.r][v.c] = true;
                count++;
                q.push(v);
            }
        }
    }

    return count;
}

int main() {
    while (true) {
       scanf("%d %d", &N, &M);
       if (N == 0)
           break;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }

        map<int, int> result;
        int numberOfSlicks = 0;
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (matrix[i][j] == 1 && !visited[i][j]) {
                    int slickSize = BFS(Point(i, j));
                    result[slickSize]++;
                    numberOfSlicks++;
                }
            }
        }

        printf("%d\n", numberOfSlicks);
        for (map<int, int>::iterator it = result.begin(); it != result.end(); ++it) {
            printf("%d %d\n", it->first, it->second);
        }
    }

    return 0;
}
