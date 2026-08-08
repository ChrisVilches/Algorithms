#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool findSafeWalk(const vector<vector<int>>& grid, const int health) {
    const int n = grid.size();
    const int m = grid.front().size();

    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    priority_queue<tuple<int, int, int>> pq;
    pq.emplace(grid.front().front(), 0, 0);
    dist.front().front() = grid.front().front();

    while (!pq.empty()) {
      const auto [_, i, j] = pq.top();
      pq.pop();

      for (const auto& [i2, j2] : {
               pair<int, int>{i + 1, j},
               {i - 1, j},
               {i, j + 1},
               {i, j - 1},
           }) {
        if (i2 < 0 || j2 < 0 || i2 == n || j2 == m) continue;

        const int alt = dist[i][j] + grid[i2][j2];

        if (alt < dist[i2][j2]) {
          dist[i2][j2] = alt;
          pq.emplace(-alt, i2, j2);
        }
      }
    }

    return health - dist.back().back() >= 1;
  }
};
