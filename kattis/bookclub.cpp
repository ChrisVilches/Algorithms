#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> Graph;

bool bpm(const Graph& g, const int u, vector<bool>& visited, vector<int>& match) {
  for (const int v : g[u]) {
    if (visited[v]) continue;
    visited[v] = true;

    if (match[v] == -1 || bpm(g, match[v], visited, match)) {
      match[v] = u;
      return true;
    }
  }

  return false;
}

int max_bipartite_matching(const Graph& g, const int match_set_size) {
  vector<int> match(match_set_size, -1);
  vector<bool> visited(match_set_size);
  int result = 0;
  for (int u = 0; u < (int)g.size(); u++) {
    fill(visited.begin(), visited.end(), false);
    result += bpm(g, u, visited, match);
  }
  return result;
}

int main() {
  int N, M;

  cin >> N >> M;

  Graph g(N);

  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
  }

  cout << (max_bipartite_matching(g, N) == N ? "YES" : "NO") << endl;
}
