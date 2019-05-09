// Problem: 1837. Isenbaev's Number
// Link: http://acm.timus.ru/problem.aspx?space=1&num=1837
// Solution: Mai Thanh Hiep

#include <iostream>
#include <string>
#include <map>
#include <queue>
using namespace std;

#define INF 1e9
#define MAX 300 // max 300 members because max 100 teams and each team have 3 members

void bfs(vector<vector<int>>& graph, int src, vector<int>& dist) {
    queue<int> q;
    q.push(src);
    dist[src] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];

            // If v is not visited yet
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    int n;
    cin >> n;

    string str1, str2, str3;
    int id1, id2, id3;
    map<string, int> mapIds;
    int id = 0;
    vector<vector<int>> graph(MAX);
    for (int i = 0; i < n; i++) {
        cin >> str1 >> str2 >> str3;
        if (mapIds.find(str1) == mapIds.end())
            mapIds[str1] = id++;

        if (mapIds.find(str2) == mapIds.end())
            mapIds[str2] = id++;

        if (mapIds.find(str3) == mapIds.end())
            mapIds[str3] = id++;

        id1 = mapIds[str1];
        id2 = mapIds[str2];
        id3 = mapIds[str3];

        graph[id1].push_back(id2);
        graph[id1].push_back(id3);
        graph[id2].push_back(id1);
        graph[id2].push_back(id3);
        graph[id3].push_back(id1);
        graph[id3].push_back(id2);
    }

    vector<int> dist(MAX, -1);
    // only bfs if found Isenbaev member
    if (mapIds.find("Isenbaev") != mapIds.end()) {
        bfs(graph, mapIds["Isenbaev"], dist);
    }

    for (map<string, int>::iterator it = mapIds.begin(); it != mapIds.end(); ++it) {
        cout << it->first << " ";
        if (dist[it->second] == -1) // can't reach
            cout << "undefined" << endl;
        else
            cout << dist[it->second] << endl;
    }

	return 0;
}
