// Problem: 729 - The Hamming Distance Problem
// Link: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=670
// Author: Mai Thanh Hiep
// Complexity: O(2^N), N <= 16

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void backtracking(int H, string& result, int i, int bit1Counter) {
    int n = result.size();
    if (i == n) {
        if (bit1Counter == H) {
            cout << result << endl;
        }
    } else {
        for (char ch = '0'; ch <= '1'; ch++) {
            if (ch == '1')
                bit1Counter++;

            if (bit1Counter <= H) {
                result[i] = ch;
                backtracking(H, result, i + 1, bit1Counter);
            }

            // since bit1Counter is local variable, we don't need to backtrack
            // if (ch == '1')
            //	bit1Counter--;
        }
    }
}

int main() {
    int T, N, H;
    cin >> T;

    string result;
    bool needPrintBlankLine = false;
    while (T--) {
        if (needPrintBlankLine)
            cout << endl;
        needPrintBlankLine = true;

        cin >> N >> H;
        result.resize(N);
        backtracking(H, result, 0, 0);
    }

    return 0;
}