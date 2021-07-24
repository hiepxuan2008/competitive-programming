// Problem: TRYCOMP - Try to complete
// Link: https://www.spoj.com/problems/TRYCOMP/
// Author: Mai Thanh Hiep
// Complexity: O(L1 + L2), where L1 <= 5*10^6 is total number of characters in input words, L2 <= 10^6 is total number of characters in queries words.

#include <iostream>
#include <algorithm>
using namespace std;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

struct TrieNode {
    static const int MAX = 26;
    TrieNode* child[MAX] = {};
    int mostFreq = 0;
    string mostFreqStr = "";
    int cnt = 0;
};

int dfsAddWord(TrieNode* root, const string& word, int depth) {
    if (root == nullptr) return 0;
    if (depth == word.length()) {
        root->cnt += 1;
        return root->cnt;
    }
    char c = word[depth] - 'a';
    if (root->child[c] == nullptr) {
        root->child[c] = new TrieNode();
    }
    int freq = dfsAddWord(root->child[c], word, depth + 1);
    if (root->child[c]->mostFreq < freq) {
        root->child[c]->mostFreq = freq;
        root->child[c]->mostFreqStr = word;
    } else if (root->child[c]->mostFreq == freq && root->child[c]->mostFreqStr > word) {
        root->child[c]->mostFreqStr = word;
    }
    return freq;
}

void search(TrieNode* root, const string& prefix) {
    TrieNode* curr = root;
    for (char c : prefix) {
        c -= 'a';
        if (curr->child[c] == nullptr) {
            cout << -1 << '\n';
            return;
        }
        curr = curr->child[c];
    }
    cout << curr->mostFreqStr << " " << curr->mostFreq << '\n';
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n;
    string word, s;
    TrieNode* root = new TrieNode();
    for (int i= 0; i < n; ++i) {
        cin >> word;
        dfsAddWord(root, word, 0);
    }
    cin >> q;
    while (q--) {
        cin >> s;
        search(root, s);
    }
    return 0;
}