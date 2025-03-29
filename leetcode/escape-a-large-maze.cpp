#include <bits/stdc++.h>
using namespace std;

class Solution {
  int grid[500][500];
  const int max_val = 1'000'000;
  vector<int> end{max_val, max_val};

  void dfs(const int i, const int j) {
    if (i < 0 || j < 0 || i > end[1] || j > end[0]) return;
    if (grid[i][j] != 0) return;
    grid[i][j] = 2;
    dfs(i + 1, j);
    dfs(i - 1, j);
    dfs(i, j + 1);
    dfs(i, j - 1);
  }

 public:
  bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source,
                        vector<int>& target) {
    array<vector<pair<int, int>>, 2> coords;

    for (int i = 0; i < 2; i++) {
      coords[i].emplace_back(source[i], -1);
      coords[i].emplace_back(target[i], -2);
      coords[i].emplace_back(end[i], -3);
      coords[i].emplace_back(0, -4);
    }

    for (size_t i = 0; i < blocked.size(); i++) {
      for (int j = 0; j < 2; j++) {
        coords[j].emplace_back(blocked[i][j], i);
      }
    }

    for (auto& v : coords) sort(v.begin(), v.end());

    for (int i = 0; i < 2; i++) {
      int curr = 0;
      int prev_val = coords[i][0].first;
      for (const auto& [raw, idx] : coords[i]) {
        curr += min(abs(raw - prev_val), 2);
        prev_val = raw;

        if (idx == -1) {
          source[i] = curr;
        } else if (idx == -2) {
          target[i] = curr;
        } else if (idx == -3) {
          end[i] = curr;
        } else if (idx >= 0) {
          blocked[idx][i] = curr;
        }
      }
    }

    memset(grid, 0, sizeof grid);

    for (const vector<int>& vec : blocked) {
      grid[vec.front()][vec.back()] = 1;
    }

    dfs(source.front(), source.back());

    return grid[target.front()][target.back()] == 2;
  }
};
