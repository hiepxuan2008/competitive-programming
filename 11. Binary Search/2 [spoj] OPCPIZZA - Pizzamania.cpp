// Solution: OPCPIZZA - Pizzamania
// Link: https://www.spoj.com/problems/OPCPIZZA
// Solution: Mai Thanh Hiep

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 100000
long long arr[MAX];

int main() {
    int t;
    cin >> t;

    int n;
    long long m;
    while (t--) {
        cin >> n >> m;

        for (int i = 0; i < n; i++)
            cin >> arr[i];

        sort(arr, arr + n);

        int i = 0;
        int j = n - 1;
        int cnt = 0;
        while (i < j) {
            if (arr[i] + arr[j] == m) {
                cnt++;
                i++;
                j--;
            } else if (arr[i] + arr[j] > m) {
                j--;
            } else {
                i++;
            }
        }

        cout << cnt << endl;
    }

    return 0;
}
