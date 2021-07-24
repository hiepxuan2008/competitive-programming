// Problem: CHN16I: Alice and Bob play Contact
// Link: https://www.codechef.com/problems/CHN16I
// Author: Mai Thanh Hiep
// Complexity: O(L), where L <= 10^6 is total number of characters of strings in A array and B array.

#include <iostream>
#include <algorithm>
#include <vector>
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
    vector<int> goList;
    for (char c : prefix) {
        c -= 'a';
        if (curr->child[c] == nullptr) break;
        curr = curr->child[c];
        goList.push_back(curr->go);
    }
    if (goList.empty()) return 0;
    int i = 1;
    int ans = 0;
    for (int j = goList.size() - 1; j >= 0; --j) {
        if (goList[j] >= i) {
            ++ans;
            i++;
        }
    }
    return ans;
}

const int MAXN = 1e5 + 5;
string A[MAXN], B[MAXN];

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        TrieNode* root = new TrieNode();
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
        }
        for (int i = 0; i < m; ++i) {
            cin >> B[i];
            addWord(root, B[i]);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += search(root, A[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}