#include <bits/stdc++.h>
using namespace std;

class Solution {
  using pii = pair<int, int>;

  pii rotate(const pii dir) const { return {dir.second, -dir.first}; };
  pii add(const pii pos, const pii dir) const {
    return {pos.first + dir.first, pos.second + dir.second};
  }

  bool valid(const pii pos, const vector<vector<int>>& matrix) const {
    const int n = matrix.size();
    const int m = matrix.front().size();

    if (pos.first < 0 || pos.second < 0 || pos.first >= n || pos.second >= m)
      return false;

    return matrix[pos.first][pos.second] != INT_MIN;
  }

 public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    const size_t n = matrix.size();
    const size_t m = matrix.front().size();

    vector<int> res;

    pii pos{0, 0}, dir{0, 1};

    while (res.size() < n * m) {
      const int elem = matrix[pos.first][pos.second];
      res.emplace_back(elem);
      if (!valid(add(pos, dir), matrix)) dir = rotate(dir);
      matrix[pos.first][pos.second] = INT_MIN;
      pos = add(pos, dir);
    }

    return res;
  }
};
