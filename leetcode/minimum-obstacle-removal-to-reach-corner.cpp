#include <bits/stdc++.h>
using namespace std;

class Solution {
  typedef tuple<int, int, int> tiii;
  const int di[4]{-1, 1, 0, 0};
  const int dj[4]{0, 0, -1, 1};

 public:
  int minimumObstacles(vector<vector<int>>& grid) {
    const int N = grid.size();
    const int M = grid.front().size();

    vector<vector<int>> dist(N, vector<int>(M, INT_MAX));

    priority_queue<tiii, vector<tiii>, greater<tiii>> q;

    q.emplace(0, 0, 0);
    dist[0][0] = 0;

    while (!q.empty()) {
      const auto [_, i, j] = q.top();
      q.pop();

      for (int d = 0; d < 4; d++) {
        const int i2 = i + di[d];
        const int j2 = j + dj[d];

        if (i2 < 0 || j2 < 0 || i2 >= N || j2 >= M) continue;

        const int alt = dist[i][j] + grid[i2][j2];

        if (alt < dist[i2][j2]) {
          dist[i2][j2] = alt;
          q.emplace(alt, i2, j2);
        }
      }
    }

    return dist.back().back();
  }
};
