// Problem: 510 C. Fox And Names
// Link: http://codeforces.com/problemset/problem/510/C
// Author: Mai Thanh Hiep
// Complexity: O(ALPHABET_SIZE + N), N <= 100, ALPHABET_SIZE = 26 -> This is complexity of this solution

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

bool topologicalSort(int V, vector<vector<int>> &graph, vector<int> &result) {
    vector<int> inDegree(V, 0);
    queue<int> zeroDegree;

    for (int u = 0; u < V; u++) {
        for (int v : graph[u]) {
            inDegree[v]++;
        }
    }

    for (int u = 0; u < V; u++) {
        if (inDegree[u] == 0) {
            zeroDegree.push(u);
        }
    }

    while (!zeroDegree.empty()) {
        int u = zeroDegree.front(); zeroDegree.pop();
        result.push_back(u);
        for (int v : graph[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                zeroDegree.push(v);
            }
        }
    }

    return result.size() == V;
}

int findFirstDifferent(string& str1, string& str2) {
    int n = min(str1.size(), str2.size());
    for (int i = 0; i < n; i++)
        if (str1[i] != str2[i])
            return i;
    return -1;
}

#define ALPHABET_SIZE 26

string solve(int n, vector<string>& names) {
    vector<vector<int>> graph(ALPHABET_SIZE, vector<int>());
    string str1, str2;
    for (int i = 1; i < n; i++) {
        str1 = names[i - 1];
        str2 = names[i];
        int first = findFirstDifferent(str1, str2);
        if (first == -1) {
            if (str1.size() > str2.size())
                return "Impossible";
        } else {
            graph[str1[first] - 'a'].push_back(str2[first] - 'a'); // str1[first] < str2[first]
        }
    }

    vector<int> topoOrder;
    bool success = topologicalSort(ALPHABET_SIZE, graph, topoOrder); // O(ALPHABET_SIZE + N), N <= 100, ALPHABET_SIZE=26 -> This is complexity of this solution
    if (!success)
        return "Impossible";

    string result(ALPHABET_SIZE, ' ');
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        result[i] = topoOrder[i] + 'a';
    }
    return result;
}

int main() {
    int n;
    cin >> n;

    vector<string> names(n);
    for (int i = 0; i < n; i++) {
        cin >> names[i];
    }

    string result = solve(n, names);
    cout << result << endl;

    return 0;
}