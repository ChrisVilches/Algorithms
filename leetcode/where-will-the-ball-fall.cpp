#include <bits/stdc++.h>
using namespace std;

class Solution {
  int query(int j, vector<vector<int>>& grid) {
    const int m = grid.front().size();

    for (const auto& row : grid) {
      const int dir = row[j];
      const int j2 = j + dir;

      if (j2 < 0 || m <= j2 || row[j] != row[j2]) return -1;

      j += dir;
    }

    return j;
  }

 public:
  vector<int> findBall(vector<vector<int>>& grid) {
    vector<int> ans;

    const int m = grid.front().size();

    for (int i = 0; i < m; i++) {
      ans.emplace_back(query(i, grid));
    }

    return ans;
  }
};
