// Topic: Basic Trie Implementation
// Source: BigO Center

#include <iostream>
#include <algorithm>
using namespace std;

struct TrieNode {
    static const int MAX = 26;
    TrieNode* child[MAX] = {};
    int cnt = 0;
    bool isEmpty() {
        for (int i = 0; i < MAX; ++i)
            if (child[i] != nullptr) return false;
        return true;
    }
};

void addWord(TrieNode* root, const string& s) {
    TrieNode* cur = root;
    for (char c : s) {
        c -= 'a';
        if (cur->child[c] == nullptr) {
            cur->child[c] = new TrieNode();
        }
        cur = cur->child[c];
    }
    cur->cnt += 1;
}

bool removeWordDFS(TrieNode* root, const string& s, int depth = 0) {
    if (root == nullptr) return false;
    if (depth == s.length()) {
        if (root->cnt > 0) {
            root->cnt--;
            return true;
        }
        return false;
    }
    int c = s[depth] - 'a';
    bool needRemove = removeWordDFS(root->child[c], s, depth + 1);
    if (needRemove && root->child[c]->cnt == 0 && root->child[c]->isEmpty()) {
        delete root->child[c];
        root->child[c] = nullptr;
    }
    return needRemove;
}

bool search(TrieNode* root, const string& s) {
    TrieNode* cur = root;
    for (char c : s) {
        c -= 'a';
        if (cur->child[c] == nullptr) return false;
        cur = cur->child[c];
    }
    return cur->cnt > 0;
}

int main() {
    TrieNode* root = new TrieNode();
    addWord(root, "bigo");
    addWord(root, "complete");
    addWord(root, "algo");
    addWord(root, "algorithm");
    cout << search(root, "competitive") << '\n';
    cout << search(root, "bigo") << '\n';
    cout << search(root, "algorithm") << '\n';
    removeWordDFS(root, "algorithm");
    cout << search(root, "algorithm") << '\n';
    return 0;
}