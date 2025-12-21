#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minRectanglesToCoverPoints(vector<vector<int>>& points, const int w) {
    sort(points.begin(), points.end());

    int ans = 0;

    int prev_x = -1;

    for (const vector<int>& p : points) {
      const int x = p.front();

      if (prev_x == -1 || x - prev_x > w) {
        prev_x = x;
        ans++;
      }
    }

    return ans;
  }
};
