#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> graph;

bool visited[26];

vector<int> connected_component(graph& g, int node) {
  vector<int> result;
  queue<int> q;
  q.push(node);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    result.push_back(u);
    visited[u] = true;

    for (int v : g[u]) {
      if (visited[v]) continue;
      q.push(v);
      visited[v] = true;
    }
  }
  sort(result.begin(), result.end());
  return result;
}

void solve() {
  memset(visited, 0, sizeof visited);
  int V, E;
  cin >> V >> E;
  graph g(V, vector<int>{});
  for (int i = 0; i < E; i++) {
    char u, v;
    scanf(" %c %c ", &u, &v);
    int node_u = u - 'a';
    int node_v = v - 'a';

    g[node_u].push_back(node_v);
    g[node_v].push_back(node_u);
  }

  int count = 0;

  for (int i = 0; i < V; i++) {
    if (visited[i]) continue;
    count++;
    vector<int> component = connected_component(g, i);
    for (int node : component) printf("%c,", node + 'a');
    cout << endl;
  }
  cout << count << " connected components" << endl << endl;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    printf("Case #%d:\n", i + 1);
    solve();
  }
}
