#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  double operator*(const Point p) const { return x * p.x + y * p.y; }
  Point rot_ccw(const double t) const {
    return {x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)};
  }
  double cross(const Point p) const { return x * p.y - y * p.x; }
  double dist(const Point p) const { return hypot(x - p.x, y - p.y); }
};

double angle_adhoc(const Point a, const Point b) { return atan2(a.cross(b), a * b); }
double angle_adhoc(const Point o, const Point a, const Point b) {
  return angle_adhoc(a - o, b - o);
}

class Solution {
 public:
  vector<double> internalAngles(const vector<int>& sides) {
    if (sides[0] >= sides[1] + sides[2]) return {};
    if (sides[1] >= sides[0] + sides[2]) return {};
    if (sides[2] >= sides[0] + sides[1]) return {};

    const Point a{0, 0};
    const Point b{static_cast<double>(sides[0]), 0};

    double lo = 0;
    double hi = M_PI;

    for (int iter = 0; iter < 100; iter++) {
      const double mid = (lo + hi) / 2;
      const Point c = b + Point{static_cast<double>(sides[1]), 0}.rot_ccw(mid);

      if (c.dist(a) > sides[2]) {
        lo = mid;
      } else {
        hi = mid;
      }
    }

    const Point c = b + Point{static_cast<double>(sides[1]), 0}.rot_ccw(lo);

    vector<double> angles;

    angles.emplace_back(angle_adhoc(a, b, c) * 180 / M_PI);
    angles.emplace_back(angle_adhoc(b, c, a) * 180 / M_PI);
    angles.emplace_back(angle_adhoc(c, a, b) * 180 / M_PI);

    sort(angles.begin(), angles.end());

    return angles;
  }
};
