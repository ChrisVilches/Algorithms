#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  int cross(const Point p) const { return x * p.y - y * p.x; }
  int dist2(const Point p) const {
    const Point r = *this - p;
    return r.x * r.x + r.y * r.y;
  }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  bool operator==(const Point p) const { return x == p.x && y == p.y; }
  static Point from_vec(const vector<int>& v) { return {v.front(), v.back()}; }
};

bool ccw(const Point o, const Point p, const Point q) { return (p - o).cross(q - o) > 0; }

class Solution {
 public:
  bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
    vector<Point> square{
        Point::from_vec(p1),
        Point::from_vec(p2),
        Point::from_vec(p3),
        Point::from_vec(p4),
    };

    const Point o = square.front();
    sort(square.begin() + 1, square.end(),
         [o](const Point p, const Point q) { return ccw(o, p, q); });

    if (square[0] == square[1]) return false;
    if (!ccw(square[0], square[1], square[2])) return false;
    if (!ccw(square[0], square[1], square[3])) return false;

    const int side2 = square[0].dist2(square[1]);
    const int diag2 = square[0].dist2(square[2]);

    for (int i = 0; i < 4; i++) {
      if (square[i].dist2(square[(i + 1) % 4]) != side2) return false;
      if (square[i].dist2(square[(i + 2) % 4]) != diag2) return false;
    }

    return true;
  }
};
