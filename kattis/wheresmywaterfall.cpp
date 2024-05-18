#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
bool visited[2001][2001];

int main() {
  int n, m, k;

  while (cin >> n >> m >> k) {
    grid.resize(n);
    memset(visited, 0, sizeof visited);
    queue<pair<int, int>> q;
    for (int i = 0; i < k; i++) {
      int x;
      cin >> x;
      q.emplace(0, x);
    }

    for (auto& row : grid) cin >> row;

    while (!q.empty()) {
      const auto [i, j] = q.front();
      q.pop();

      if (grid[i][j] == '~') continue;
      grid[i][j] = '~';

      if (i + 1 == n) continue;

      if (grid[i + 1][j] == 'O') {
        q.emplace(i + 1, j);
      } else if (grid[i + 1][j] == '#' || grid[i + 1][j] == '?') {
        if (j > 0 && grid[i][j - 1] == 'O') {
          q.emplace(i, j - 1);
        }
        if (j < m - 1 && grid[i][j + 1] == 'O') {
          q.emplace(i, j + 1);
        }
      }
    }

    for (const auto& row : grid) {
      cout << row << endl;
    }
  }
}
