#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int latestDayToCross(const int n, const int m, vector<vector<int>>& cells) {
    vector<vector<int>> days(n, vector<int>(m));

    for (size_t i = 0; i < cells.size(); i++) {
      const int u = cells[i].front() - 1;
      const int v = cells[i].back() - 1;
      days[u][v] = i + 1;
    }

    vector<vector<bool>> vis(n, vector<bool>(m));

    const function<bool(int, int, int)> dfs = [&](const int day, const int i,
                                                  const int j) {
      if (i < 0 || j < 0 || i >= n || j >= m) return false;
      if (days[i][j] <= day) return false;
      if (vis[i][j]) return false;
      if (i == n - 1) return true;
      vis[i][j] = true;
      return dfs(day, i + 1, j) || dfs(day, i, j + 1) || dfs(day, i, j - 1) ||
             dfs(day, i - 1, j);
    };

    int lo = 0;
    int hi = n * m;

    while (lo <= hi) {
      const int mid = (lo + hi) / 2;

      for (auto& row : vis) fill(row.begin(), row.end(), false);

      bool ok = false;

      for (int i = 0; i < m && !ok; i++) {
        if (dfs(mid, 0, i)) ok = true;
      }

      if (ok) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return lo - 1;
  }
};
