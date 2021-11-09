#include <bits/stdc++.h>

using namespace std;

char grid[103][103];
int rings[103][103], ring_tmp[103][103];

int N, M;

void solve() {
  int remaining_trees;

  do {
    remaining_trees = 0;

    vector<pair<int, int>> trees;

    for (int i = 1; i <= N; i++)
      for (int j = 1; j <= M; j++) {
        if (grid[i][j] != 'T') continue;
        remaining_trees++;

        char up = grid[i - 1][j];
        char below = grid[i + 1][j];
        char left = grid[i][j - 1];
        char right = grid[i][j + 1];

        if (up == '.' || below == '.' || left == '.' || right == '.')
          trees.push_back(make_pair(i, j));
      }

    memcpy(ring_tmp, rings, sizeof(rings));

    for (pair<int, int>& tree : trees) {
      auto [i, j] = tree;
      int prev_ring = max({ring_tmp[i - 1][j], ring_tmp[i + 1][j],
                           ring_tmp[i][j - 1], ring_tmp[i][j + 1]});

      rings[i][j] = prev_ring + 1;
      grid[i][j] = '.';
    }
  } while (remaining_trees > 0);
}

int chars_necessary() {
  int ring_total = 0;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) ring_total = max(ring_total, rings[i][j]);

  return ring_total < 10 ? 2 : 3;
}

void cout_number(int n, int chars) {
  string num = n == 0 ? "." : to_string(n);
  while ((int)num.size() < chars) num = '.' + num;
  cout << num;
}

int main() {
  cin >> N >> M;

  memset(grid, '.', sizeof grid);

  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) cin >> grid[i][j];

  solve();

  int chars = chars_necessary();

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) cout_number(rings[i][j], chars);
    cout << endl;
  }
}
