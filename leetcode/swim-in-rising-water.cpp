#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool visited[51][51];
  const int di[4]{-1, 1, 0, 0};
  const int dj[4]{0, 0, -1, 1};

 public:
  int swimInWater(const vector<vector<int>>& grid) {
    const int n = grid.size();

    int lo = 0;
    int hi = 50 * 50 + 7;

    const function<void(int, int, int)> dfs = [&](const int i, const int j, const int t) {
      if (visited[i][j]) return;
      if (grid[i][j] > t) return;

      visited[i][j] = true;

      for (int d = 0; d < 4; d++) {
        const int i2 = i + di[d];
        const int j2 = j + dj[d];
        if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= n) continue;

        dfs(i2, j2, t);
      }
    };

    while (lo < hi) {
      const int mid = (lo + hi) / 2;

      memset(visited, 0, sizeof visited);
      dfs(0, 0, mid);

      if (visited[n - 1][n - 1]) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }

    return lo;
  }
};
