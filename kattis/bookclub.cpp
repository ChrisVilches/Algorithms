#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> graph;

int match[10000];
bool visited[10000];

bool bpm(graph& g, int u) {
  for (int v : g[u])
    if (!visited[v]) {
      visited[v] = true;
      if (match[v] < 0 || bpm(g, match[v])) {
        match[v] = u;
        return true;
      }
    }
  return false;
}

int max_bipartite_matching(graph& g) {
  memset(match, -1, sizeof match);
  int result = 0;
  for (int u = 0; u < (int)g.size(); u++) {
    memset(visited, 0, sizeof visited);
    result += bpm(g, u);
  }
  return result;
}

int main() {
  int N, M;

  cin >> N >> M;

  graph g(N);

  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
  }

  cout << (max_bipartite_matching(g) == N ? "YES" : "NO") << endl;
}
