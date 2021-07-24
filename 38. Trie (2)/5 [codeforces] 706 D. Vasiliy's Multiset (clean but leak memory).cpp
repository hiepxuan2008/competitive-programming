// Problem: 706 D. Vasiliy's Multiset
// Link: https://codeforces.com/problemset/problem/706/D
// Author: Mai Thanh Hiep
// Complexity: O(32 * Q), where Q <= 2*10^5 is number of queries Vasiliy has to perform.

#include <iostream>
#include <algorithm>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

struct TrieNode {
    static const int MAX = 2;
    TrieNode* child[MAX] = {};
    int go = 0;
};

void increase(TrieNode* root, int number, int d) {
    TrieNode* curr = root;
    for (int i = 31; i >= 0; --i) {
        int c = (number >> i) & 1;
        if (curr->child[c] == nullptr) {
            curr->child[c] = new TrieNode();
        }
        curr = curr->child[c];
        curr->go += d;
    }
}

int findMax(TrieNode* root, int number) {
    TrieNode* curr = root;
    int ans = 0;
    for (int i = 31; i >= 0; --i) {
        int c = (number >> i) & 1;
        if (curr->child[1-c] != nullptr && curr->child[1-c]->go > 0) {
            curr = curr->child[1-c];
            ans |= (1 << i);
        } else {
            curr = curr->child[c];
        }
    }
    return ans;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q, x;
    cin >> q;
    char cmd;
    TrieNode* root = new TrieNode();
    increase(root, 0, 1);
    while (q--) {
        cin >> cmd >> x; //  1 <= x <= 10^9
        if (cmd == '+') {
            increase(root, x, 1);
        } else if (cmd == '-') {
            increase(root, x, -1);
        } else {
            cout << findMax(root, x) << '\n';
        }
    }
    return 0;
}