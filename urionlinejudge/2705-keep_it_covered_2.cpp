#include <bits/stdc++.h>
using namespace std;
using Graph = vector<vector<int>>;

const int di[]{0, 0, 1, -1};
const int dj[]{1, -1, 0, 0};

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
  int R, C;
  while (cin >> R >> C) {
    vector<string> grid(R);
    for (auto& r : grid) cin >> r;

    vector<vector<vector<int>>> nodes(R, vector<vector<int>>(C));

    int node_idx = 0;

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        nodes[i][j].push_back(node_idx++);
        if (grid[i][j] == '-') nodes[i][j].push_back(node_idx++);
      }
    }

    Graph g(node_idx);

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        for (int d = 0; d < 4; d++) {
          const int i2 = i + di[d];
          const int j2 = j + dj[d];
          if (i2 < 0 || j2 < 0 || i2 >= R || j2 >= C) continue;

          for (const int u : nodes[i][j]) {
            for (const int v : nodes[i2][j2]) {
              g[u].push_back(v);
            }
          }
        }
      }
    }

    cout << (max_bipartite_matching(g, g.size()) == (int)g.size() ? 'Y' : 'N') << endl;
  }
}
