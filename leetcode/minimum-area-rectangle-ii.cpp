#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  int operator*(const Point p) const { return x * p.x + y * p.y; }
  bool operator<(const Point p) const { return x < p.x || (x == p.x && y < p.y); }
  double dist(const Point p) const { return hypot(x - p.x, y - p.y); }
};

bool deg90(const Point o, const Point p, const Point q) { return (p - o) * (q - o) == 0; }

class Solution {
 public:
  double minAreaFreeRect(const vector<vector<int>>& input) {
    vector<Point> points;

    for (const auto& vec : input) {
      points.push_back(Point{vec.front(), vec.back()});
    }

    const set<Point> s{points.begin(), points.end()};

    double ans = DBL_MAX;

    for (const Point p : points) {
      for (const Point q : points) {
        for (const Point k : points) {
          if (!deg90(p, q, k)) continue;

          const Point vec = k - p;
          const Point other = q + vec;

          if (!s.count(other)) continue;

          const double side1 = p.dist(q);
          const double side2 = p.dist(k);
          const double area = side1 * side2;

          if (area > 0) {
            ans = min(ans, area);
          }
        }
      }
    }

    if (ans == DBL_MAX) return 0;
    return ans;
  }
};
