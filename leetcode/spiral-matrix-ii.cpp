#include <bits/stdc++.h>
using namespace std;

class Solution {
  using pii = pair<int, int>;

  pii rotate(const pii dir) const { return {dir.second, -dir.first}; };
  pii add(const pii pos, const pii dir) const {
    return {pos.first + dir.first, pos.second + dir.second};
  }

  bool valid(const pii pos, const vector<vector<int>>& grid) const {
    const int n = grid.size();
    if (pos.first < 0 || pos.second < 0 || pos.first >= n || pos.second >= n)
      return false;

    return grid[pos.first][pos.second] == -1;
  }

 public:
  vector<vector<int>> generateMatrix(const int n) {
    vector<vector<int>> res(n, vector<int>(n, -1));

    pii pos{0, 0}, dir{0, 1};

    for (int total = 0; total < n * n; pos = add(pos, dir)) {
      res[pos.first][pos.second] = ++total;
      if (!valid(add(pos, dir), res)) dir = rotate(dir);
    }

    return res;
  }
};
