// Problem: Search Engine
// Link: https://www.hackerearth.com/practice/data-structures/advanced-data-structures/trie-keyword-tree/practice-problems/algorithm/search-engine/?fbclid=IwAR0h_gLNfeHAz4w1c9KRRoAU6OFfln-p-urZCilCsK_vvUqF1ZGhVw4Q5vM
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string>
using namespace std;

#define MAX 26

struct Node {
    Node* child[MAX];
    int countWord;
    int priority;

    Node() {
        countWord = 0;
        priority = -1;
        for (int i = 0; i < MAX; i++)
            child[i] = NULL;
    }
};

void addWord(Node* root, const string& s, int priority) {
    int ch;
    Node* temp = root;
    for (int i = 0; i < s.size(); i++) {
        ch = s[i] - 'a';
        if (temp->child[ch] == NULL)
            temp->child[ch] = new Node();
        temp = temp->child[ch];
        temp->priority = max(temp->priority, priority);
    }
    temp->countWord++;
}

bool isWord(Node* root) {
    return root != NULL && root->countWord > 0;
}

int findMaxPriorityMatch(Node* root, const string& s) {
    int ch;
    Node* temp = root;
    for (int i = 0; i < s.size(); i++) {
        ch = s[i] - 'a';
        if (temp->child[ch] == NULL)
            return -1; // not found
        temp = temp->child[ch];
    }

    return temp->priority;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    Node* root = new Node();
    string s;
    int priority;
    for (int i = 0; i < n; i++) {
        cin >> s >> priority;
        addWord(root, s, priority);
    }

    for (int i = 0; i < q; i++) {
        cin >> s;
        cout << findMaxPriorityMatch(root, s) << endl;
    }

    return 0;
}
