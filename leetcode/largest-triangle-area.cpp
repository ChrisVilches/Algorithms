#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  int cross(const Point p) const { return x * p.y - y * p.x; }
};

class Solution {
 public:
  double largestTriangleArea(const vector<vector<int>>& points) {
    const int n = points.size();

    double ans = 0;

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        for (int k = j + 1; k < n; k++) {
          const Point o{points[i].front(), points[i].back()};
          const Point a{points[j].front(), points[j].back()};
          const Point b{points[k].front(), points[k].back()};

          ans = max(ans, abs((a - o).cross(b - o)) / 2.0);
        }
      }
    }

    return ans;
  }
};
