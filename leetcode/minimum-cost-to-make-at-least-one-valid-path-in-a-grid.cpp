#include <bits/stdc++.h>
using namespace std;

class Solution {
  const array<int, 4> di{0, 0, 1, -1};
  const array<int, 4> dj{1, -1, 0, 0};

 public:
  int minCost(const vector<vector<int>>& grid) {
    const int n = grid.size();
    const int m = grid.front().size();

    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    priority_queue<tuple<int, int, int>> pq;

    dist[0][0] = 0;
    pq.emplace(0, 0, 0);

    while (!pq.empty()) {
      const auto [_, i, j] = pq.top();
      pq.pop();

      for (int d = 0; d < 4; d++) {
        const int i2 = i + di[d];
        const int j2 = j + dj[d];

        if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m) continue;

        const int alt = dist[i][j] + (d != grid[i][j] - 1);

        if (alt < dist[i2][j2]) {
          dist[i2][j2] = alt;
          pq.emplace(-alt, i2, j2);
        }
      }
    }

    return dist.back().back();
  }
};
