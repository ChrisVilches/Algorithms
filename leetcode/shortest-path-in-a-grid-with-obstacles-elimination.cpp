#include <bits/stdc++.h>
using namespace std;

class Solution {
  typedef tuple<int, int, int, int> tiiii;
  const int di[4]{-1, 1, 0, 0};
  const int dj[4]{0, 0, -1, 1};
  bool visited[40][40][40 * 40];

 public:
  int shortestPath(vector<vector<int>>& grid, int k) {
    const int N = grid.size();
    const int M = grid.front().size();

    queue<tiiii> q;
    q.emplace(0, 0, k, 0);
    visited[0][0][k] = true;

    while (!q.empty()) {
      const auto [i, j, k, dist] = q.front();
      q.pop();

      if (i == N - 1 && j == M - 1) return dist;

      for (int d = 0; d < 4; d++) {
        const int i2 = i + di[d];
        const int j2 = j + dj[d];
        if (i2 < 0 || j2 < 0 || i2 >= N || j2 >= M) continue;
        const int k2 = k - (grid[i2][j2] == 1);

        if (k2 < 0) continue;
        if (visited[i2][j2][k2]) continue;

        visited[i2][j2][k2] = true;
        q.emplace(i2, j2, k2, dist + 1);
      }
    }

    return -1;
  }
};
