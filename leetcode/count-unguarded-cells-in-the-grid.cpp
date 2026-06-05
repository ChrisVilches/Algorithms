#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int countUnguarded(const int n, const int m, const vector<vector<int>>& guards,
                     const vector<vector<int>>& walls) {
    vector<vector<pair<int, char>>> rows(n), cols(m);
    vector<vector<bool>> grid(n, vector<bool>(m, true));

    for (const vector<int>& g : guards) {
      const int i = g.front();
      const int j = g.back();
      rows[i].emplace_back(j, 'g');
      cols[j].emplace_back(i, 'g');
      grid[i][j] = false;
    }

    for (const vector<int>& w : walls) {
      const int i = w.front();
      const int j = w.back();
      rows[i].emplace_back(j, 'w');
      cols[j].emplace_back(i, 'w');
      grid[i][j] = false;
    }

    for (auto& x : rows) sort(x.begin(), x.end());
    for (auto& x : cols) sort(x.begin(), x.end());

    for (int i = 0; i < n; i++) {
      const auto& row = rows[i];

      for (size_t x = 0; x <= row.size(); x++) {
        const auto prev = x == 0 ? make_pair(-1, '?') : row[x - 1];
        const auto curr = x == row.size() ? make_pair(m, '?') : row[x];

        if (prev.second == 'g' || curr.second == 'g') {
          for (int k = prev.first + 1; k < curr.first; k++) {
            grid[i][k] = false;
          }
        }
      }
    }

    for (int i = 0; i < m; i++) {
      const auto& col = cols[i];

      for (size_t x = 0; x <= col.size(); x++) {
        const auto prev = x == 0 ? make_pair(-1, '?') : col[x - 1];
        const auto curr = x == col.size() ? make_pair(n, '?') : col[x];

        if (prev.second == 'g' || curr.second == 'g') {
          for (int k = prev.first + 1; k < curr.first; k++) {
            grid[k][i] = false;
          }
        }
      }
    }

    int ans = 0;

    for (const vector<bool>& row : grid) {
      ans += accumulate(row.begin(), row.end(), 0);
    }

    return ans;
  }
};
