// Problem: ADAINDEX - Ada and Indexing
// Link: https://www.spoj.com/problems/ADAINDEX/
// Author: Mai Thanh Hiep
// Complexity: O(L1 + L2), where L1 <= 10^6 is total number of characters in input words, L2 <= 10^6 is total number of characters in queries words.

#include <iostream>
#include <algorithm>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

struct TrieNode {
    static const int MAX = 26;
    TrieNode* child[MAX] = {};
    int go = 0;
};

void addWord(TrieNode* root, const string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        c -= 'a';
        if (curr->child[c] == nullptr) {
            curr->child[c] = new TrieNode();
        }
        curr = curr->child[c];
        curr->go += 1;
    }
}

int search(TrieNode* root, const string& prefix) {
    TrieNode* curr = root;
    for (char c : prefix) {
        c -= 'a';
        if (curr->child[c] == nullptr) return 0;
        curr = curr->child[c];
    }
    return curr->go;
}

int main() {
//    fin;
    int n, q;
    string word;
    cin >> n >> q;
    TrieNode* root = new TrieNode();
    for (int i = 0; i < n; ++i) {
        cin >> word;
        addWord(root, word);
    }
    while (q--) {
        cin >> word;
        cout << search(root, word) << '\n';
    }
    return 0;
}