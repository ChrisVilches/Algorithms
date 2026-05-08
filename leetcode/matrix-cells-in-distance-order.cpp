#include <bits/stdc++.h>
using namespace std;

class Solution {
  using pii = pair<int, int>;

 public:
  vector<vector<int>> allCellsDistOrder(const int rows, const int cols, const int r,
                                        const int c) {
    queue<pii> q;
    q.emplace(r, c);
    vector<vector<bool>> vis(rows, vector<bool>(cols, false));
    vis[r][c] = true;
    vector<vector<int>> ans;

    while (!q.empty()) {
      const auto [i, j] = q.front();
      q.pop();
      ans.push_back(vector<int>{i, j});

      for (const auto [i2, j2] : {pii{i + 1, j}, {i, j + 1}, {i - 1, j}, {i, j - 1}}) {
        if (i2 < 0 || j2 < 0 || i2 == rows || j2 == cols) continue;
        if (vis[i2][j2]) continue;
        vis[i2][j2] = true;
        q.emplace(i2, j2);
      }
    }

    return ans;
  }
};
