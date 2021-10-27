#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> graph;

char grid[21][21];
int R, C;
bool visited[21 * 21 * 2];
int match[21 * 21 * 2];
int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};

bool bpm(graph& g, int u) {
  for (int v : g[u]) {
    if (visited[v]) continue;
    visited[v] = true;
    if (match[v] < 0 || bpm(g, match[v])) {
      match[v] = u;
      return true;
    }
  }
  return false;
}

int max_bipartite_matching(graph g) {
  memset(match, -1, sizeof match);
  int result = 0;
  for (int u = 0; u < (int)g.size(); u++) {
    memset(visited, 0, sizeof visited);
    if (bpm(g, u)) result++;
  }
  return result;
}

void read_grid() {
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      while (scanf("%c", &grid[i][j]) &&
             !(grid[i][j] == 'o' || grid[i][j] == '-'))
        ;
    }
  }
}

graph build_graph() {
  pair<vector<int>, vector<int>> nodes[R][C];
  pair<int, int> nodes_idx[R][C];

  int idx = 0;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      nodes_idx[i][j].first = idx++;
      if (grid[i][j] == '-') nodes_idx[i][j].second = idx++;
    }
  }

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if ((i + j) % 2 != 0) continue;

      for (int d = 0; d < 4; d++) {
        int i2 = i + di[d];
        int j2 = j + dj[d];
        if (i2 < 0 || j2 < 0 || i2 >= R || j2 >= C) continue;

       // pair<vector<int>, vector<int>>& curr_cell = nodes[i][j];
       // pair<vector<int>, vector<int>>& curr_cell = nodes[i][j];


        nodes[i][j].first.push_back(nodes_idx[i2][j2].first);
        nodes[i2][j2].first.push_back(nodes_idx[i][j].first);

        if (grid[i2][j2] == '-') {
          nodes[i][j].first.push_back(nodes_idx[i2][j2].second);
          nodes[i2][j2].second.push_back(nodes_idx[i][j].first);
        }

        if (grid[i][j] == '-') {
          nodes[i][j].second.push_back(nodes_idx[i2][j2].first);
          nodes[i2][j2].first.push_back(nodes_idx[i][j].second);
          if (grid[i2][j2] == '-') {
            nodes[i][j].second.push_back(nodes_idx[i2][j2].second);
            nodes[i2][j2].second.push_back(nodes_idx[i][j].second);
          }
        }
      }
    }
  }

  graph g;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      g.push_back(nodes[i][j].first);
      if (grid[i][j] == '-') g.push_back(nodes[i][j].second);
    }
  }

  return g;
}

void solve() {
  read_grid();
  graph g = build_graph();

  cout << (max_bipartite_matching(g) == g.size() ? 'Y' : 'N') << endl;
}

int main() {
  while (scanf("%d %d", &R, &C) == 2) solve();
}
