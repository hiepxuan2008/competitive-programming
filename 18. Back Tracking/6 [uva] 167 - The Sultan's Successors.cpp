// Problem: 167 - The Sultan's Successors
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=103
// Author: Mai Thanh Hiep

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string.h>
using namespace std;
#define N 8
vector<vector<pair<int, int>>> result;

void printSolution(bool board[N][N]) {
    vector<pair<int, int>> path(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 1) {
                path[i] = make_pair(i, j);
                break;
            }
        }
    }
    result.push_back(path);
}

bool isSafe(bool board[N][N], int row, int col) {
    int i, j;

    /* Check this row on left side */
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    /* Check upper diagonal on left side */
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    /* Check lower diagonal on left side */
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

void NQueen(bool board[N][N], int col) {
    if (col >= N) {
        printSolution(board);
        return;
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = true;
            NQueen(board, col + 1);
            board[i][col] = false; // BACKTRACK 
        }
    }
}

int main() {
    int k;
    cin >> k;

    bool board[N][N];
    memset(board, 0, sizeof(board));
    NQueen(board, 0);

    int scoreBoard[N][N];
    while (k--) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> scoreBoard[i][j];
            }
        }

        int ans = 0;
        int score;
        for (int i = 0; i < result.size(); i++) {
            score = 0;
            for (int j = 0; j < result[i].size(); j++) {
                score += scoreBoard[result[i][j].first][result[i][j].second];
            }
            ans = max(score, ans);
        }

        cout << right << setw(5) << ans << endl;
    }

    return 0;
}