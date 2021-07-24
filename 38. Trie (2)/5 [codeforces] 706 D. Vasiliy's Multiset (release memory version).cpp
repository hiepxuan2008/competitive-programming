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
    int cnt = 0;
    bool isEmpty() {
        for (int i = 0; i < MAX; ++i)
            if (child[i] != nullptr) return false;
        return true;
    }
};

void addWord(TrieNode* root, int number) {
    TrieNode* curr = root;
    for (int i = 31; i >= 0; --i) {
        int c = (number >> i) & 1;
        if (curr->child[c] == nullptr) {
            curr->child[c] = new TrieNode();
        }
        curr = curr->child[c];
    }
    curr->cnt += 1;
}

bool removeWordDFS(TrieNode* root, int number, int bitAt = 31) {
    if (root == nullptr) return false;
    if (bitAt == -1) {
        root->cnt -= 1;
        return root->cnt == 0;
    }
    int c = (number >> bitAt) & 1;
    bool needRemove = removeWordDFS(root->child[c], number, bitAt - 1);
    if (needRemove && root->child[c]->cnt == 0 && root->child[c]->isEmpty()) {
        delete root->child[c];
        root->child[c] = nullptr;
    }
    return needRemove;
}

int findMax(TrieNode* root, int number) {
    TrieNode* curr = root;
    int ans = 0;
    for (int i = 31; i >= 0; --i) {
        int c = (number >> i) & 1;
        if (curr->child[1-c] != nullptr) {
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
    addWord(root, 0);
    while (q--) {
        cin >> cmd >> x; //  1 <= x <= 10^9
        if (cmd == '+') {
            addWord(root, x);
        } else if (cmd == '-') {
            removeWordDFS(root, x);
        } else {
            cout << findMax(root, x) << '\n';
        }
    }
    return 0;
}