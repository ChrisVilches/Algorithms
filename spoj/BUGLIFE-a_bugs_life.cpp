#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
enum { NONE = 0, RED = 1, BLACK = 2 };

short nodes[2001];

inline short inv(short color) { return color == RED ? BLACK : RED; }

bool bipartite(vector<vi>& graph, int node) {
  queue<int> q;
  q.push(node);
  nodes[node] = RED;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : graph[u]) {
      if (nodes[v] == NONE) {
        nodes[v] = inv(nodes[u]);
        q.push(v);
      } else if (nodes[v] == nodes[u]) {
        return false;
      }
    }
  }
  return true;
}

void solve() {
  memset(nodes, NONE, sizeof nodes);
  int n, m;
  cin >> n >> m;
  vector<vi> g(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  for (int i = 0; i < n; i++) {
    if (nodes[i] != NONE) continue;
    if (!bipartite(g, i)) {
      cout << "Suspicious bugs found!" << endl;
      return;
    }
  }

  cout << "No suspicious bugs found!" << endl;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    printf("Scenario #%d:\n", i + 1);
    solve();
  }
}
