// Problem: UCI2009D - Digger Octaves
// Link: https://vn.spoj.com/problems/UCI2009D/
// Author: Mai Thanh Hiep
// Complexity: T * O(N^2 * 4 * 3^6), N <= 8

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <string.h>
using namespace std;

#define MAXN 8
#define OCTAVES 8
const int dc[] = { 0, 1, 0, -1 };
const int dr[] = { -1, 0, 1, 0 };

bool isInBoard(int r, int c, int sizeOfBoard) {
	return r >= 0 && r < sizeOfBoard && c >= 0 && c < sizeOfBoard;
}

int getPosInLongLong(int r, int c) {
	return r * OCTAVES + c;
}

void setBit(long long &x, int k) {
	x |= 1LL << k;
}

void clearBit(long long &x, int k) {
	x &= ~(1LL << k);
}

void countOctaves(int N, int r, int c, int step, long long path, char board[MAXN][MAXN], set<long long>& octaveSet) {
	board[r][c] = '.'; // marked as visited
	setBit(path, getPosInLongLong(r, c));

	if (step == OCTAVES) {
		octaveSet.insert(path);
	} else {
		for (int j = 0; j < 4; j++) {
			int nr = r + dr[j];
			int nc = c + dc[j];

			if (isInBoard(nr, nc, N) && board[nr][nc] == 'X') {
				countOctaves(N, nr, nc, step + 1, path, board, octaveSet);
			}
		}
	}

	board[r][c] = 'X'; // backtrack
	clearBit(path, getPosInLongLong(r, c));
}

int main() {
	char board[MAXN][MAXN];
	int T, N;
	cin >> T;
	while (T--) {
		cin >> N;

		for (int r = 0; r < N; r++)
			for (int c = 0; c < N; c++)
				cin >> board[r][c];

		set<long long> octaveSet;
		long long path;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (board[r][c] == 'X') {
					path = 0LL;
					countOctaves(N, r, c, 1, path, board, octaveSet);
				}
			}
		}

		cout << octaveSet.size() << endl;
	}
	return 0;
}