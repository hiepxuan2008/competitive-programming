// Problem: 890 C. Petya and Catacombs
// Link: https://codeforces.com/problemset/problem/890/C
// Author: Mai Thanh Hiep
// Complexity: O(N)

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n;

    vector<bool> room(n, false);
    for (int i = 0; i < n; i++) {
        cin >> x;
        room[x] = true;
    }

    int count = 1;
    for (int i = 0; i < n; i++) {
        if (!room[i]) {
            count++;
        }
    }
    cout << count;
    
    return 0;
}