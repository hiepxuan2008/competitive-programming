// Problem: 1200 E. Compress Words
// Link: https://codeforces.com/problemset/problem/1200/E
// Author: Mai Thanh Hiep
// Complexity: O(N), where N <= 10^5 is the length of string

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
ll BASE = 79; // Ascii in range [48-122] -> 75 chars -> choose 79 (prime) as BASE

class PolyHash {
public:
    PolyHash(const string& str) {
        int n = str.size();
        preHash.resize(n+1);
        POW.resize(n+1);
        preHash[0] = 0;
        POW[0] = 1;
        for (int i = 0; i < n; i++) {
            preHash[i+1] = preHash[i] * BASE + str[i] - '0' + 1;
            POW[i+1] = POW[i] * BASE;
        }
    }

    ll getHash(int l, int r) {
        ++l;
        ++r;
        return preHash[r] - preHash[l-1] * POW[r-l+1];
    }

    void extend(const string& str) {
        for (int i = 0; i < str.size(); i++) {
            preHash.push_back(preHash.back() * BASE + str[i] - '0' + 1);
            POW.push_back(POW.back() * BASE);
        }
    }
private:
    vector<ll> preHash;
    vector<ll> POW;
};

string substring(const string &str, int left, int right) { // left, right inclusive
    return str.substr(left, right - left + 1);
}

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }
    string ans = words[0];
    PolyHash polyHash1(words[0]);
    for (int i = 1; i < n; ++i) {
        string& currentWord = words[i];
        PolyHash polyHash2(currentWord);
        int size1 = ans.size(), size2 = currentWord.size();
        int longestLength = 0;
        for (int l = min(size1, size2); l >= 1; --l) {
            if (polyHash1.getHash(size1-l, size1-1) == polyHash2.getHash(0, l-1) &&
                substring(ans, size1-l, size1-1) == substring(currentWord, 0, l-1)) { // Double check -> exit early -> don't change time complexity so much
                longestLength = l;
                break;
            }
        }
        string newStr = currentWord.substr(longestLength, size2 - longestLength);
        ans += newStr;
        polyHash1.extend(newStr);
    }
    cout << ans << endl;
    return 0;
}