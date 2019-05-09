// Problem: A. Night at the Museum
// Link: http://codeforces.com/contest/731/problem/A
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string>

using namespace std;

int getDistance(char c1, char c2) {
    if (c1 > c2)
        return c1 - c2;
    return c2 - c1;
}

int main() {
    string str;
    cin >> str;

    int ans = 0;
    char cur = 'a';
    int dist;
    for (int i = 0; i < str.length(); i++) {
        dist = getDistance(str[i], cur);
        ans += min(dist, 26 - dist);
        cur = str[i];
    }
    cout << ans << endl;

    return 0;
}