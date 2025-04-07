#include <bits/stdc++.h>
using namespace std;

#define x front()
#define y back()

class Solution {
 public:
  int minTimeToVisitAllPoints(const vector<vector<int>>& points) {
    const int n = points.size();

    int ans = 0;

    for (int i = 0; i < n - 1; i++) {
      const auto& p = points[i];
      const auto& q = points[i + 1];

      ans += max(abs(p.x - q.x), abs(p.y - q.y));
    }

    return ans;
  }
};
