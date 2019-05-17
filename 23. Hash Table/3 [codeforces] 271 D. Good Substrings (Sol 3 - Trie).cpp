// Prolem: 271 D. Good Substrings
// Link: http://codeforces.com/problemset/problem/271/D
// Author: Mai Thanh Hiep
// Complexity: O(|S|^2), |S| <= 1500
// Status: ACCEPTED

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

struct Node {
	Node* child[ALPHABET_SIZE];
	int count;

	Node() {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			child[i] = NULL;
		}
		count = 0;
	}
};

void deleteTrie(Node* root) {
	if (root == NULL)
		return;

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		deleteTrie(root->child[i]);
	}
	delete root;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string s, strBadChars;
	int k;
	cin >> s >> strBadChars >> k;

	int ans = 0;
	Node* trie = new Node();
	Node* current;
	char ch;
	for (int i = 0, n = s.length(), badCharCounter; i < n; i++) { // O(|S|^2), |S| <= 1500
		badCharCounter = 0;
		current = trie;
		for (int j = i; j < n; j++) {
			ch = s[j];

			if (strBadChars[ch - 'a'] == '0')
				badCharCounter++;

			if (badCharCounter > k)
				break;

			if (current->child[ch - 'a'] == NULL) {
				current->child[ch - 'a'] = new Node();
			}

			if (current->child[ch - 'a']->count == 0) {
				current->child[ch - 'a']->count++;
				ans++;
			}

			current = current->child[ch - 'a'];
		}
	}
	deleteTrie(trie);

	cout << ans << endl;

	return 0;
}