// Problem: The Monk and Prateek
// Link: https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/practice-problems/algorithm/the-monk-and-prateek/
// Author: Mai Thanh Hiep
// Complexity: O(N * log(x)), N <= 10^5, x <= 10^7

#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

// O(Log(x))
int fhash(int x) {
    int n = x;
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n = n / 10;
    }
    return x ^ sum;
}

int main() {
    int n;
    cin >> n;
    unordered_map<int, int> mapTimes;

    for (int i = 0, x; i < n; i++) { // O(N) * Log(x)
        cin >> x;
        mapTimes[fhash(x)]++;
    }

    int collision = 0;
    int fMaxCollisionSmallestValue = -1;
    int fMaxCollisionTimes = -1;
    bool allHashAreUnique = true;
    int maxHash = -1;
    for (unordered_map<int, int>::iterator it = mapTimes.begin(); it != mapTimes.end(); ++it) {
        if (it->second > 1) {
            collision += it->second - 1;
        }

        if (fMaxCollisionTimes < it->second) {
            fMaxCollisionTimes = it->second;
            fMaxCollisionSmallestValue = it->first;
        } else if (fMaxCollisionTimes == it->second && fMaxCollisionSmallestValue > it->first) {
            fMaxCollisionSmallestValue = it->first;
        }

        if (it->second != 1)
            allHashAreUnique = false;

        maxHash = max(it->first, maxHash);
    }

    int result = fMaxCollisionSmallestValue; // Note 2: If there are multiple hashed values which occur the maximum number of times, print the smallest hashed value with the maximum count.
    if (allHashAreUnique) // Note 1: If all the values of the function are unique, print the maximum value which occurs in the list of the hashed values.
        result = maxHash;

    cout << result << " " << collision << endl;

    return 0;
}