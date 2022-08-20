#include <bits/stdc++.h>
using namespace std;

class Solution {
  typedef pair<int, int> pii;
  int N, M;
  vector<vector<char>> grid;
  const int di[4]{-1, 1, 0, 0};
  const int dj[4]{0, 0, -1, 1};
  bool visited[21][21][4];

  pii find(const vector<vector<char>>& grid, const char c) {
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
        if (grid[i][j] == c) return {i, j};
    assert(false);
  }

  bool valid_position(const pii& pos) {
    const auto [i, j] = pos;
    if (i < 0 || j < 0 || i >= N || j >= M) return false;
    return grid[i][j] != '#';
  }

  bool has_path(const pii& start, const pii& box, const pii& target) {
    vector<vector<bool>> vis(N, vector<bool>(M, false));
    const function<bool(int, int)> dfs = [&](const int i, const int j) {
      if (!valid_position({i, j}) || vis[i][j]) return false;
      vis[i][j] = true;
      if (make_pair(i, j) == box) return false;
      if (make_pair(i, j) == target) return true;
      for (int d = 0; d < 4; d++)
        if (dfs(i + di[d], j + dj[d])) return true;
      return false;
    };
    return dfs(start.first, start.second);
  }

 public:
  int minPushBox(vector<vector<char>>& grid) {
    this->grid = grid;
    this->N = grid.size();
    this->M = grid.front().size();

    memset(visited, 0, sizeof visited);

    const auto T = find(grid, 'T');

    queue<tuple<pii, pii, int>> q;
    q.emplace(find(grid, 'S'), find(grid, 'B'), 0);

    while (!q.empty()) {
      const auto [prev, b, moves] = q.front();
      q.pop();

      if (b == T) return moves;

      for (int d = 0; d < 4; d++) {
        const pii back = {b.first + di[d], b.second + dj[d]};
        const pii b2 = {b.first - di[d], b.second - dj[d]};

        if (!valid_position(back) || !valid_position(b2)) continue;
        if (visited[b2.first][b2.second][d]) continue;
        if (!has_path(prev, b, back)) continue;

        visited[b2.first][b2.second][d] = true;
        q.emplace(b, b2, moves + 1);
      }
    }

    return -1;
  }
};
