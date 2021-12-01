#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> graph;

int N;
char grid[101][101];
short rows[101][101], cols[101][100];
bool visited[10000];
int match[10000];

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

void solve() {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) scanf(" %c", &grid[i][j]);

  int row = -1, col = -1;
  for (int i = 0; i < N; i++) {
    bool pawn_col = true, pawn_row = true;
    for (int j = 0; j < N; j++) {
      if (grid[i][j] == '.' && pawn_row) row++;
      rows[i][j] = row;
      pawn_row = grid[i][j] == 'X';

      if (grid[j][i] == '.' && pawn_col) col++;
      cols[j][i] = col;
      pawn_col = grid[j][i] == 'X';
    }
  }

  graph g(row + col + 2);

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (grid[i][j] != 'X') {
        int row = rows[i][j];
        int col = cols[i][j];
        g[row].push_back(col);
      }

  printf("%d\n", max_bipartite_matching(g));
}

int main() {
  while (scanf("%d", &N) == 1) solve();
}
