#include <bits/stdc++.h>
using namespace std;

#define V 100
int g[V][V];

bool bfs(int (&rgraph)[V][V], int s, int t, int parent[]) {
  bool visited[V];
  memset(visited, 0, sizeof(visited));

  queue<int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v = 0; v < V; v++) {
      if (visited[v] == false && rgraph[u][v] > 0) {
        if (v == t) {
          parent[v] = u;
          return true;
        }
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  return false;
}

int ford_fulkerson(int (&g)[V][V], int s, int t) {
  int u, v, parent[V], max_flow = 0, rgraph[V][V];

  for (u = 0; u < V; u++)
    for (v = 0; v < V; v++) rgraph[u][v] = g[u][v];

  while (bfs(rgraph, s, t, parent)) {
    int path_flow = INT_MAX;
    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      path_flow = min(path_flow, rgraph[u][v]);
    }

    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      rgraph[u][v] -= path_flow;
      rgraph[v][u] += path_flow;
    }

    max_flow += path_flow;
  }

  return max_flow;
}

void solve() {
  int N, M;
  cin >> N >> M;

  memset(g, 0, sizeof g);

  int source = 0;
  map<string, int> size_node;
  size_node["XXL"] = 1;
  size_node["XL"] = 2;
  size_node["L"] = 3;
  size_node["M"] = 4;
  size_node["S"] = 5;
  size_node["XS"] = 6;

  // Connect source to all sizes
  for (int i = 1; i <= (int)size_node.size(); i++) {
    g[source][i] = N / 6;
  }

  int volunteer_offset = 7;  // 1 source + 6 sizes
  int target = volunteer_offset + M;

  for (int i = 0; i < M; i++) {
    string s1, s2;
    cin >> s1 >> s2;
    int volunteer_node = volunteer_offset + i;
    g[size_node[s1]][volunteer_node] = 1;
    g[size_node[s2]][volunteer_node] = 1;
    g[volunteer_node][target] = 1;
  }

  int max_flow = ford_fulkerson(g, source, target);
  cout << (max_flow >= M ? "YES" : "NO") << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
