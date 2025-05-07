#include <bits/stdc++.h>
using namespace std;

class Solution {
  const int di[4]{-1, 1, 0, 0};
  const int dj[4]{0, 0, -1, 1};

 public:
  vector<vector<int>> highestPeak(const vector<vector<int>>& isWater) {
    const int n = isWater.size();
    const int m = isWater.front().size();
    queue<tuple<int, int, int>> q;
    vector<vector<int>> res(n, vector<int>(m, -1));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (isWater[i][j] == 1) {
          q.emplace(i, j, 0);
          res[i][j] = 0;
        }
      }
    }

    while (!q.empty()) {
      const auto [i, j, h] = q.front();
      q.pop();
      for (int d = 0; d < 4; d++) {
        const int i2 = i + di[d];
        const int j2 = j + dj[d];
        if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m) continue;
        if (res[i2][j2] != -1) continue;
        res[i2][j2] = h + 1;
        q.emplace(i2, j2, h + 1);
      }
    }

    return res;
  }
};
