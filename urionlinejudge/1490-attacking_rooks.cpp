#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> Graph;

string grid[101];
short rows[101][101], cols[101][101];

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
  int N;

  while (cin >> N) {
    for (int i = 0; i < N; i++) cin >> grid[i];

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

    Graph g(row + 1);

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        const int r = rows[i][j];
        const int c = cols[i][j];
        if (grid[i][j] == '.') {
          g[r].push_back(c);
        }
      }
    }

    cout << max_bipartite_matching(g, col + 1) << endl;
  }
}
