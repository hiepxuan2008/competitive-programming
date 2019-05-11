// Problem: 183 - Bit Maps
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=119
// Author: Mai Thanh Hiep

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void BtoD(const vector<vector<char>> &bm, int startRow, int endRow, int startCol, int endCol, int &printedCharsCount) {
	if (startRow > endRow || startCol > endCol)
		return;

	int zeros = 0;
	for (int r = startRow; r <= endRow; r++) {
		for (int c = startCol; c <= endCol; c++) {
			if (bm[r][c] == '0')
				zeros++;
		}
	}

	// Each line will contain up to 50 characters.
	if (printedCharsCount > 0 && printedCharsCount % 50 == 0)
		cout << endl;
	++printedCharsCount;
	if (zeros == (endRow - startRow + 1) * (endCol - startCol + 1))
		cout << "0";
	else if (zeros == 0)
		cout << "1";
	else {
		cout << "D";
		int halfRow = (startRow + endRow) >> 1;
		int halfCol = (startCol + endCol) >> 1;
		BtoD(bm, startRow, halfRow, startCol, halfCol, printedCharsCount);
		BtoD(bm, startRow, halfRow, halfCol + 1, endCol, printedCharsCount);
		BtoD(bm, halfRow + 1, endRow, startCol, halfCol, printedCharsCount);
		BtoD(bm, halfRow + 1, endRow, halfCol + 1, endCol, printedCharsCount);
	}
}

void DtoB(vector<vector<char>> &bm, int startRow, int endRow, int startCol, int endCol) {
	if (startRow > endRow || startCol > endCol)
		return;

	// Get 1 char from cin.
	char ch;
	cin >> ch;
	if (ch == '0' || ch == '1') {
		for (int r = startRow; r <= endRow; ++r)
			for (int c = startCol; c <= endCol; ++c)
				bm[r][c] = ch;
	}
	else {
		int halfRow = (startRow + endRow) >> 1;
		int halfCol = (startCol + endCol) >> 1;
		DtoB(bm, startRow, halfRow, startCol, halfCol);
		DtoB(bm, startRow, halfRow, halfCol + 1, endCol);
		DtoB(bm, halfRow + 1, endRow, startCol, halfCol);
		DtoB(bm, halfRow + 1, endRow, halfCol + 1, endCol);
	}
}

int main() {
	char type;
	int row, col;
	while (cin >> type && type != '#') {
		cin >> row >> col;

		// The width and height are to be output right justified in fields of width four.
		cout << (type == 'B' ? "D" : "B")
			<< right << setw(4) << row
			<< right << setw(4) << col
			<< endl;

		vector<vector<char>> bm(row, vector<char>(col));
		switch (type) {
		case 'B': {
			string s;
			while (s.size() < row * col) {
				string tmp;
				getline(cin, tmp);
				s = s + tmp;
			}
			for (int r = 0; r < row; ++r)
				for (int c = 0; c < col; ++c)
					bm[r][c] = s[r * col + c];

			int printedCharsCount = 0;
			BtoD(bm, 0, row - 1, 0, col - 1, printedCharsCount);
			break;
		}
		case 'D': {
			DtoB(bm, 0, row - 1, 0, col - 1);

			int printedCharsCount = 0;
			for (int r = 0; r < row; ++r) {
				for (int c = 0; c < col; ++c) {
					// Each line will contain up to 50 characters.
					if (printedCharsCount > 0 && printedCharsCount % 50 == 0)
						cout << endl;
					cout << bm[r][c];
					printedCharsCount++;
				}
			}
			break;
		}
		}
		cout << endl;
	}
	return 0;
}