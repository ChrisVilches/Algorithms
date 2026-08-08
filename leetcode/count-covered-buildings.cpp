#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int countCoveredBuildings(const int n, const vector<vector<int>>& buildings) {
    unordered_map<int, int> min_x, max_x, min_y, max_y;

    for (const vector<int>& point : buildings) {
      const int x = point.front();
      const int y = point.back();

      if (!min_x.count(y)) min_x[y] = x;
      if (!max_x.count(y)) max_x[y] = x;
      if (!min_y.count(x)) min_y[x] = y;
      if (!max_y.count(x)) max_y[x] = y;

      min_y[x] = min(min_y[x], y);
      max_y[x] = max(max_y[x], y);
      min_x[y] = min(min_x[y], x);
      max_x[y] = max(max_x[y], x);
    }

    int ans = 0;

    for (const vector<int>& point : buildings) {
      const int x = point.front();
      const int y = point.back();

      if (x == min_x[y] || x == max_x[y]) continue;
      if (y == min_y[x] || y == max_y[x]) continue;

      ans++;
    }

    return ans;
  }
};
