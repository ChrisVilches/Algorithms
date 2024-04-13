#include <bits/stdc++.h>
using namespace std;

const int di[]{-1, 1, 0, 0};
const int dj[]{0, 0, -1, 1};

class Solution {
  int n, m;
  vector<vector<int>> grid, times;

  bool possible(const int t0) {
    queue<tuple<int, int, int>> q;
    q.emplace(0, 0, t0);
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    visited[0][0] = true;
    while (!q.empty()) {
      const auto [i, j, t] = q.front();
      q.pop();

      for (int d = 0; d < 4; d++) {
        const int i2 = i + di[d];
        const int j2 = j + dj[d];
        if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m) continue;
        if (visited[i2][j2] || grid[i2][j2] == 2) continue;

        if (i2 == n - 1 && j2 == m - 1) return times[i2][j2] >= t + 1;
        if (t + 1 >= times[i2][j2]) continue;

        visited[i2][j2] = true;
        q.emplace(i2, j2, t + 1);
      }
    }

    return false;
  }

 public:
  int maximumMinutes(vector<vector<int>>& grid) {
    n = grid.size();
    m = grid.front().size();
    this->grid = grid;
    times.assign(n, vector<int>(m, INT_MAX));
    queue<tuple<int, int, int>> q;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == 1) {
          q.emplace(i, j, 0);
        }
      }
    }

    while (!q.empty()) {
      const auto [i, j, t] = q.front();
      q.pop();
      times[i][j] = t;
      for (int d = 0; d < 4; d++) {
        const int i2 = i + di[d];
        const int j2 = j + dj[d];
        if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m) continue;
        if (times[i2][j2] != INT_MAX || grid[i2][j2] == 2) continue;
        q.emplace(i2, j2, t + 1);
      }
    }

    int lo = 0;
    int hi = 1e9;

    while (lo <= hi) {
      const int mid = (lo + hi) / 2;
      if (possible(mid)) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return hi;
  }
};
