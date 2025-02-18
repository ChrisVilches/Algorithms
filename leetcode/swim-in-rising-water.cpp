#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool visited[51][51];

 public:
  int swimInWater(const vector<vector<int>>& grid) {
    const int n = grid.size();

    int lo = 0;
    int hi = 50 * 50 + 7;

    const function<void(int, int, int)> dfs = [&](const int i, const int j, const int t) {
      if (i < 0 || j < 0 || i >= n || j >= n) return;
      if (visited[i][j]) return;
      if (grid[i][j] > t) return;

      visited[i][j] = true;
      dfs(i + 1, j, t);
      dfs(i - 1, j, t);
      dfs(i, j + 1, t);
      dfs(i, j - 1, t);
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
