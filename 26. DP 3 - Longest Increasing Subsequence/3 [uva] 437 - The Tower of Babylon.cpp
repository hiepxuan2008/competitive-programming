// Problem: 437 - The Tower of Babylon
// Link: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=378
// Author: Mai Thanh Hiep
// Complexity: T * O((6N)^2), N <= 30

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct Block {
    int length, width, height;
    Block(int _length, int _width, int _height) : length(_length), width(_width), height(_height) {}
};

// O(N^2)
int highestSubSequence(const vector<Block>& arr, int n) {
    vector<int> dp(n, 0);

    for (int i = 0; i < arr.size(); i++) {
        dp[i] = arr[i].height;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i].length < arr[j].length && arr[i].width < arr[j].width) {
                dp[i] = max(dp[i], dp[j] + arr[i].height);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, dp[i]);
    return ans;
}

bool sortDecreasingByLengthAndThenDecreasingByWidth(const Block& a, const Block& b) {
    if (a.length == b.length)
        return a.width > b.width;
    return a.length > b.length;
}

int main() {
    int n, tc = 0;

    while (cin >> n) {
        if (n == 0)
            break;

        vector<Block> arr;
        int x, y, z;
        for (int i = 0; i < n; i++) {
            cin >> x >> y >> z;
            // Generate all permutations of this block type
            arr.push_back(Block(x, y, z));
            arr.push_back(Block(x, z, y));
            arr.push_back(Block(y, x, z));
            arr.push_back(Block(y, z, x));
            arr.push_back(Block(z, x, y));
            arr.push_back(Block(z, y, x));
        }

        sort(arr.begin(), arr.end(), sortDecreasingByLengthAndThenDecreasingByWidth);

        cout << "Case " << ++tc << ": maximum height = " << highestSubSequence(arr, arr.size()) << endl;
    }

    return 0;
}