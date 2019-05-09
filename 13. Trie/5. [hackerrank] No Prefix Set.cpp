// Problem: No Prefix Set
// Link: https://www.hackerrank.com/challenges/no-prefix-set/problem
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define MAX 'j'-'a'+1 // lowercase letters from a->j (both inclusive).

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
	string firstFailedStr;
	for (int i = 0; i < n; i++) {
		cin >> s;

		if (!failedAddWordOccur) {
			if (!addWord(root, s)) {
				failedAddWordOccur = true;
				firstFailedStr = s;
			}
		}
	}

	if (failedAddWordOccur) {
		cout << "BAD SET" << endl;
		cout << firstFailedStr << endl;
	} else {
		cout << "GOOD SET" << endl;
	}

	destroyTrie(root);

	return 0;
}
