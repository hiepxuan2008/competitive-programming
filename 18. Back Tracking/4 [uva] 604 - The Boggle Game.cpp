// Problem: 604 - The Boggle Game
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=545
// Author: Mai Thanh Hiep
// Complexity: 
//			- Ways to choose legal words: 16*8*7*7=6272
//			- Using set<string>: O(NlogN)
//			=> Complexity: T * O(6272 * Log(6272))

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <string.h>
using namespace std;

#define N 4
#define NUM_LETTERS 4
const int dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
const int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

bool isVowelInPigEwu(char c) {
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y'; // y is consider a vowel in PigEwu
}

bool isInBoard(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < N;
}

void boggle(int r, int c, int step, string& pigewuWord, char board[N][N], bool visited[N][N], set<string>& pigewuList, int vowelCounter) {
    pigewuWord[step - 1] = board[r][c];
    visited[r][c] = true;
    if (isVowelInPigEwu(board[r][c]))
        vowelCounter++;

    if (vowelCounter <= 2) {
        if (step == NUM_LETTERS) {
            if (vowelCounter == 2) {
                pigewuList.insert(pigewuWord);
            }
        } else {
            for (int j = 0; j < 8; j++) {
                int nr = r + dr[j];
                int nc = c + dc[j];

                if (isInBoard(nr, nc) && !visited[nr][nc]) {
                    boggle(nr, nc, step + 1, pigewuWord, board, visited, pigewuList, vowelCounter);
                }
            }
        }
    }

    visited[r][c] = false;
    // since vowelCounter is local variable, we don't need to restore vowelCounter
}

int main() {
    char board1[N][N];
    char board2[N][N];
    bool visited[N][N];
    bool printNewLine = false;
    char c;
    while (true) {
        cin >> c;
        if (c == '#')
            break;
        cin.unget();

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++)
                cin >> board1[r][c];
            for (int c = 0; c < N; c++)
                cin >> board2[r][c];
        }

        set<string> pigewuList1, pigewuList2;
        string pigewuWord(NUM_LETTERS, ' ');
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                memset(visited, 0, sizeof(visited));
                boggle(r, c, 1, pigewuWord, board1, visited, pigewuList1, 0);

                memset(visited, 0, sizeof(visited));
                boggle(r, c, 1, pigewuWord, board2, visited, pigewuList2, 0);
            }
        }

        if (printNewLine)
            cout << endl;
        printNewLine = true;
        bool found = false;
        // intersect of pigewuList1 and pigewuList2
        for (set<string>::const_iterator it = pigewuList1.begin(), e = pigewuList1.end(); it != e; ++it) {
            if (pigewuList2.find(*it) != pigewuList2.end()) {
                found = true;
                cout << *it << endl;
            }
        }

        if (!found)
            cout << "There are no common words for this pair of boggle boards.\n";
    }
    return 0;
}