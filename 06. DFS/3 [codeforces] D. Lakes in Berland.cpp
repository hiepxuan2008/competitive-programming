// Problem: D. Lakes in Berland
// Link: https://codeforces.com/problemset/problem/723/D
// Solution: Mai Thanh Hiep
// Complexity: O(lakeSize-k + n*m) = O((n*m)^2)=O(250^2)=6250 (consider lai do phuc tap bai nay)
// Comment: We can use either BFS or DFS so solve this problem

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
#define MAX 50
struct Cell{
    int r;
    int c;
};

char matrix[MAX][MAX];
int visited[MAX][MAX];
int n, m, k;
int dX[] = {0, 1, 0, -1};
int dY[] = {-1, 0, 1, 0};

bool isValid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

int DFS(const Cell& startPoint, int id) {
    stack<Cell> s;
    s.push(startPoint);
    visited[startPoint.r][startPoint.c] = id;
    int count = 1;

    Cell u, v;
    while (!s.empty()) {
        u = s.top();
        s.pop();

        for (int i = 0; i < 4; i++) {
            v.r = u.r + dY[i];
            v.c = u.c + dX[i];

            if (isValid(v.r, v.c) && matrix[v.r][v.c] == '.' && visited[v.r][v.c] == -1) {
                visited[v.r][v.c] = id;
                count++;
                s.push(v);
            }
        }
    }

    return count;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);

    char endingChar;
    for (int i = 0; i < n; i++) {
        scanf("%c", &endingChar); // skip ending char
        for (int j = 0; j < m; j++) {
            scanf("%c", &matrix[i][j]);
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            visited[i][j] = -1;

    // Mark borders as non-lake
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '.' // water cell
                && (i == 0 || i == n - 1 || j == 0 || j == m - 1) // border cell
                && visited[i][j] == -1) { // not visited yet
                DFS((Cell){i, j}, 0); // mark visited[i][j] as 0 for non-lake
            }
        }
    }

    // Mark visited[i][j] as lake id
    vector<pair<int, int>> lakes;
    int id = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '.' && visited[i][j] == -1) {
                int lakeSize = DFS((Cell){i, j}, id);
                lakes.push_back(make_pair(lakeSize, id));
                id++;
            }
        }
    }

    // Sort lakes in increasing order of lake's size
    sort(lakes.begin(), lakes.end());

    // Fill lake that have less size
    int fillCellCount = 0;
    for (int z = 0; z < lakes.size() - k; z++) {
        fillCellCount += lakes[z].first;

        // Fill lake by land cells
        int id = lakes[z].second;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                if (visited[i][j] == id)
                    matrix[i][j] = '*'; // fill by land
        }
    }

    printf("%d\n", fillCellCount);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
