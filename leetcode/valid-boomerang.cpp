#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  int cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
};

class Solution {
 public:
  bool isBoomerang(const vector<vector<int>>& points) {
    const Point p{points[0][0], points[0][1]};
    const Point q{points[1][0], points[1][1]};
    const Point r{points[2][0], points[2][1]};

    return (q - p).cross(r - p) != 0;
  }
};
