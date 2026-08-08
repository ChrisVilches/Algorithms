#include <bits/stdc++.h>
using namespace std;

class Solution {
  array<pair<int, int>, 4> neighbors(const int i, const int j) const {
    return {pair<int, int>{i + 1, j}, {i - 1, j}, {i, j + 1}, {i, j - 1}};
  }

  vector<vector<int>> multisource_bfs(const vector<vector<int>>& grid) const {
    const int n = grid.size();
    queue<tuple<int, int, int>> q;
    vector<vector<int>> res(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          res[i][j] = 0;
          q.emplace(i, j, 0);
        }
      }
    }

    while (!q.empty()) {
      const auto [i, j, dist] = q.front();
      q.pop();

      for (const auto& [i2, j2] : neighbors(i, j)) {
        if (i2 < 0 || j2 < 0 || i2 == n || j2 == n) continue;
        if (res[i2][j2] != -1) continue;
        res[i2][j2] = dist + 1;
        q.emplace(i2, j2, dist + 1);
      }
    }
    return res;
  }

  int dijkstra(const vector<vector<int>>& grid) const {
    const int n = grid.size();
    vector<vector<int>> dist(n, vector<int>(n, -1));
    priority_queue<tuple<int, int, int>> pq;
    pq.emplace(grid.front().front(), 0, 0);
    dist.front().front() = grid.front().front();

    while (!pq.empty()) {
      const auto [_, i, j] = pq.top();
      pq.pop();

      for (const auto& [i2, j2] : neighbors(i, j)) {
        if (i2 < 0 || j2 < 0 || i2 == n || j2 == n) continue;

        const int alt = min(dist[i][j], grid[i2][j2]);

        if (alt > dist[i2][j2]) {
          dist[i2][j2] = alt;
          pq.emplace(alt, i2, j2);
        }
      }
    }

    return dist.back().back();
  }

 public:
  int maximumSafenessFactor(const vector<vector<int>>& grid) {
    return dijkstra(multisource_bfs(grid));
  }
};
