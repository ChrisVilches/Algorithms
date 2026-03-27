#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool canPartitionGrid(const vector<vector<int>>& grid) {
    const int n = grid.size();
    const int m = grid.front().size();

    vector<long long> rows(n, 0);
    vector<long long> cols(m, 0);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        rows[i] += grid[i][j];
        cols[j] += grid[i][j];
      }
    }

    const long long total = accumulate(rows.begin(), rows.end(), 0LL);

    for (const vector<long long>& arr : {rows, cols}) {
      long long curr = 0;

      for (const long long x : arr | views::take(arr.size() - 1)) {
        curr += x;
        if (curr * 2 == total) return true;
      }
    }

    return false;
  }
};
