#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> updateMatrix(const vector<vector<int>>& mat) {
    const int n = mat.size();
    const int m = mat.front().size();
    queue<tuple<int, int, int>> q;
    vector<vector<int>> ans(n, vector<int>(m, -1));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (mat[i][j] == 0) {
          q.emplace(i, j, 0);
          ans[i][j] = 0;
        }
      }
    }

    while (!q.empty()) {
      const auto [i, j, dist] = q.front();
      q.pop();
      for (const auto [u, v] :
           {pair<int, int>{i + 1, j}, {i, j + 1}, {i - 1, j}, {i, j - 1}}) {
        if (u < 0 || v < 0 || u == n || v == m) continue;
        if (ans[u][v] != -1) continue;
        ans[u][v] = dist + 1;
        q.emplace(u, v, dist + 1);
      }
    }

    return ans;
  }
};
