#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef pair<int, int> pii;

char grid[21][21];
int R, C;
bool visited[21 * 21 * 2];
int match[21 * 21 * 2];
int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};
pair<vi, vi> nodes[21][21];
pii nodes_idx[21][21];

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
    result += bpm(g, u);
  }
  return result;
}

void read_grid() {
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++)
      while (scanf("%c", &grid[i][j]) &&
             !(grid[i][j] == 'o' || grid[i][j] == '-'))
        ;
}

// Each cell has:
// 1 vertex if the cell is an 'o', or
// 2 vertices if the cell is a '-'.
//
// When connecting two cells, all vertices from one cell must be connected
// to the vertices of the adjacent cell.
//
// e.g. If both cells are '-', then in total there are four vertices,
// and four edges.
void connect_bidirectional(pii cell1, pii cell2) {
  auto [i, j] = cell1;
  auto [i2, j2] = cell2;
  char c1 = grid[i][j], c2 = grid[i2][j2];
  pair<vi, vi>&node1 = nodes[i][j], &node2 = nodes[i2][j2];
  pii idx1 = nodes_idx[i][j], idx2 = nodes_idx[i2][j2];

  for (int z = 0; z < 2; z++) {
    for (int x = 0; x < 2; x++) {
      for (int y = 0; y < 2; y++) {
        (x == 0 ? node1.first : node1.second)
            .push_back(y == 0 ? idx2.first : idx2.second);
        if (c2 == 'o') break;
      }

      if (c1 == 'o') break;
    }
    swap(c1, c2);
    swap(idx1, idx2);
    swap(node1, node2);
  }
}

graph build_graph() {
  int idx = 0;
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++) {
      nodes[i][j].first.clear();
      nodes[i][j].second.clear();
      nodes_idx[i][j].first = idx++;
      if (grid[i][j] == '-') nodes_idx[i][j].second = idx++;
    }

  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++) {
      if ((i + j) % 2 != 0) continue;

      for (int d = 0; d < 4; d++) {
        int i2 = i + di[d];
        int j2 = j + dj[d];
        if (i2 < 0 || j2 < 0 || i2 >= R || j2 >= C) continue;
        connect_bidirectional(make_pair(i, j), make_pair(i2, j2));
      }
    }

  graph g;

  // Transform the matrix of pairs into an adjacency list graph.
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++) {
      g.push_back(nodes[i][j].first);
      if (grid[i][j] == '-') g.push_back(nodes[i][j].second);
    }

  return g;
}

int main() {
  while (scanf("%d %d", &R, &C) == 2) {
    read_grid();
    graph g = build_graph();
    cout << (max_bipartite_matching(g) == (int)g.size() ? 'Y' : 'N') << endl;
  }
}
