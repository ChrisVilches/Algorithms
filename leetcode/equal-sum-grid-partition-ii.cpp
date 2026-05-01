#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;

  vector<vector<int>> rotate(const vector<vector<int>>& grid) const {
    const int n = grid.size();
    const int m = grid.front().size();
    vector<vector<int>> ret(m, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ret[j][n - 1 - i] = grid[i][j];
      }
    }
    return ret;
  }

  bool possible(const vector<vector<int>>& grid) const {
    const int n = grid.size();
    const int m = grid.front().size();

    unordered_map<ll, int> freq;
    ll total = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        total += grid[i][j];
        freq[grid[i][j]]++;
      }
    }

    ll curr = 0;

    for (int i = 0; i < n - 1; i++) {
      for (const ll x : grid[i]) {
        curr += x;
        freq[x]--;
        if (freq[x] == 0) freq.erase(x);
      }

      if (curr * 2 == total) return true;

      const ll excess = total - 2 * curr;

      if (m == 1) {
        if (i < n - 2 && grid.back().back() == excess) return true;
        if (i < n - 2 && grid[i + 1].back() == excess) return true;
        continue;
      }

      if (i == n - 2) {
        if (grid.back().front() == excess || grid.back().back() == excess) {
          return true;
        }
      } else {
        if (freq.count(excess)) {
          return true;
        }
      }
    }

    return false;
  }

 public:
  bool canPartitionGrid(vector<vector<int>>& grid) {
    for (int rot = 0; rot < 4; rot++) {
      if (possible(grid)) return true;
      grid = rotate(grid);
    }

    return false;
  }
};
