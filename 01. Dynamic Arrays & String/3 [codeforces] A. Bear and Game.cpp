// Problem:	A. Bear and Game
// Link: http://codeforces.com/problemset/problem/673/A
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main() {
    int n, x;
    cin >> n;

    int interestingAt = 0; // Default interesting at 0 minute
    int boringAt = -1; // Default: no boring
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x - interestingAt > 15) { // Over 15 minutes not interesting
            boringAt = interestingAt + 15;
            break;
        }
        interestingAt = x;
    }

    int ans;
    if (boringAt == -1) {
        ans = min(interestingAt + 15, 90);
    } else {
        ans = boringAt;
    }
    cout << ans << endl;

    return 0;
}
