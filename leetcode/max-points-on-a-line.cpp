#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  int cross(const Point p) const { return x * p.y - y * p.x; }
  bool above() const { return y > 0 || (y == 0 && x > 0); }
  Point to_above() const {
    if (above()) return *this;
    return {-x, -y};
  }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  bool operator<(const Point p) { return to_above().cross(p.to_above()) > 0; }
};

class Solution {
  int aux(const vector<Point>& points) {
    const int n = points.size();
    int ans = 0;
    int curr = 0;
    for (int i = 0; i < n; i++) {
      const Point p = points[i];
      const Point q = points[(i + 1) % n];
      curr++;
      ans = max(ans, curr);
      if (p.cross(q) != 0) curr = 0;
    }
    return ans;
  }

  int solve(const vector<Point>& points) {
    const int n = points.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
      vector<Point> centered;
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        centered.emplace_back(points[j] - points[i]);
      }
      sort(centered.begin(), centered.end());
      ans = max(ans, aux(centered));
    }
    return 1 + ans;
  }

 public:
  int maxPoints(vector<vector<int>>& points) {
    vector<Point> all_points;
    for (const auto& p : points) all_points.emplace_back(p[0], p[1]);
    return solve(all_points);
  }
};
