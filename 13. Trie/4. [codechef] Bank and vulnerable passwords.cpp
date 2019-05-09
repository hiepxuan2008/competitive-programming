// Problem: Bank and vulnerable passwords
// Link: https://www.codechef.com/DMNT2015/problems/BANKPASS
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define MAX 26

struct Node {
    Node* child[MAX];
    int countWord;

    Node() {
        countWord = 0;
        for (int i = 0; i < MAX; i++)
            child[i] = NULL;
    }
};

bool isWord(Node* root) {
    return root != NULL && root->countWord > 0;
}

// Return false if add failed, else return true
bool addWord(Node* root, const string& s) {
    int ch;
    Node* temp = root;
    bool hasNewChild = false;
    for (int i = 0; i < s.size(); i++) {
        ch = s[i] - 'a';
        if (temp->child[ch] == NULL) {
            temp->child[ch] = new Node();
            hasNewChild = true;
        }
        temp = temp->child[ch];

        if (!hasNewChild && isWord(temp)) { // $temp word is a prefix of $s word
			return false;
		}
    }
    temp->countWord++;
    return hasNewChild; // if hasNewChild == false -> mean $s word is prefix of another word
}

void destroyTrie(Node* root) {
    if (root == NULL)
        return;

    for (int i = 0; i < MAX; i++) {
        destroyTrie(root->child[i]);
    }
    delete root;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string s;
    cin >> n;

    Node* root = new Node();
    bool failedAddWordOccur = false;
    for (int i = 0; i < n; i++) {
        cin >> s;

        if (!failedAddWordOccur) {
            if (addWord(root, s) == false) {
                failedAddWordOccur = true;
            }
        }
    }

    cout << (failedAddWordOccur ? "vulnerable" : "non vulnerable") << endl;

    destroyTrie(root);

    return 0;
}
