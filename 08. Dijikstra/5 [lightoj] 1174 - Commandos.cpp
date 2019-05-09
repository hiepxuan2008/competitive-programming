// Problem: 1174 - Commandos
// Link: http://lightoj.com/volume_showproblem.php?problem=1174
// Solution: Mai Thanh Hiep

/*
Problem: Thả 1 bầy không giới hạn số lượng các con commando từ tòa nhà s, cho nó đi lung tung phá các tòa nhà mà nó đi qua (trong cùng 1 unit time các con commando có thể phá các tòa nhà song song), xong cho nó tập hợp tại tòa nhà cuối d
-> Tìm thời gian ngắn nhất khi các con commando xuất phát từ s phá xong tất cả các tòa nhà và tập hợp tại d nhỉ

Solution: Giả sử mỗi con commando đều đi con đường ngắn nhất xuất phát từ s, chỉ phá 1 tòa nhà và kết thúc tại d.
=> Tìm con nào đường đi dài nhất trong tất cả các con
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(int s, vector<vector<int>>& graph, vector<int>& dist) {
    queue<int> q;
    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    int n, r, u, v;
    int s, d;
    for (int x = 1; x <= T; x++) {
        cin >> n >> r;

        vector<vector<int>> graph(n);
        vector<int> dist1(n, -1);
        vector<int> dist2(n, -1);
        for (int i = 0; i < r; i++) {
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        cin >> s >> d;
        bfs(s, graph, dist1);
        bfs(d, graph, dist2);

        int longPath = 0; // long path 1 commando come from s->i->d
        for (int i = 0; i < n; i++) {
            int minPath = dist1[i] + dist2[i]; // min path of s->i->d: commando go from s to i (destroy ith building) and finish at d
            longPath = max(longPath, minPath);
        }

        cout << "Case " << x << ": " << longPath << endl;
    }

    return 0;
}
