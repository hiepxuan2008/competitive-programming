// Problem: SOCIALNE - Possible Friends
// Link: https://www.spoj.com/problems/SOCIALNE/
// Author: Mai Thanh Hiep
// Complexity: O(M^3), M <= 50
 
#include <iostream>
#include <string>
#include <vector>
 
#define INF 1e9
 
using namespace std;
 
void input(int r, string& line, vector<vector<int>>& graph, vector<vector<int>>& dist) {
    for (int c = 0; c < line.size(); c++) {
        if (r == c)
            graph[r][c] = 0;
        else if (line[c] == 'N')
            graph[r][c] = INF; // no path
        else
            graph[r][c] = 1; // path length 1
 
        dist[r][c] = graph[r][c];
    }
}
 
bool floydWarshall(vector<vector<int>>& graph, vector<vector<int>>& dist) {
    int V = graph.size();
 
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
 
    // check negative cycle
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0)
            return false;
    }
    return true;
}
 
int main() {
    int T;
    cin >> T;
    while (T--) {
        string line;
        cin >> line;
 
        int m = line.size();
        vector<vector<int>> graph(m, vector<int>(m));
        vector<vector<int>> dist(m, vector<int>(m));
 
        input(0, line, graph, dist);
 
        for (int i = 1; i < m; i++) { // O(M^2)
            cin >> line;
            input(i, line, graph, dist); // O(M)
        }
 
        floydWarshall(graph, dist); //O(M^3), M <= 50 -> This is complexity of this solution
 
        int maxPossibleFriend = 0;
        int minId = 0;
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            cnt = 0;
            for (int j = 0; j < m; j++) {
                if (dist[i][j] == 2) // Two persons are possible friends if they are not friends and they have at least one common friend
                    cnt++;
 
                if (cnt > maxPossibleFriend) {
                    maxPossibleFriend = cnt;
                    minId = i;
                }
            }
        }
 
        cout << minId << " " << maxPossibleFriend << endl;
    }
 
    return 0;
}
 