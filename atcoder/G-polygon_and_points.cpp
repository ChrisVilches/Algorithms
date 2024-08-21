#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
  ll x, y;
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  ll operator*(const Point p) const { return x * p.x + y * p.y; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  bool deg0(const Point p) const { return cross(p) == 0 && *this * p >= 0; }
};

vector<Point> polygon;

bool inside_segment(const Point p, const Point q, const Point r) {
  return (q - p).deg0(r - p) && (p - q).deg0(r - q);
}

short orientation(const Point o, const Point a, const Point b) {
  const ll x = (a - o).cross(b - o);
  return (x > 0) - (x < 0);
}

bool inside_triangle(const Point a, const Point b, const Point c, const Point p) {
  return orientation(a, b, p) >= 0 && orientation(b, c, p) >= 0 &&
         orientation(c, a, p) >= 0;
}

bool cmp(const Point p, const Point q) { return orientation(polygon[0], p, q) == -1; }

bool inside_polygon(const Point p) {
  const auto it = lower_bound(polygon.rbegin() + 1, polygon.rend() - 1, p, cmp);
  return inside_triangle(polygon[0], *it, *prev(it), p);
}

bool on_polygon_boundary(const Point p) {
  if (inside_segment(polygon.front(), polygon[1], p)) return true;
  if (inside_segment(polygon.front(), polygon.back(), p)) return true;

  const auto it = lower_bound(polygon.rbegin() + 1, polygon.rend() - 1, p, cmp);
  return inside_segment(*prev(it), *it, p);
}

int main() {
  int n, q;
  cin >> n;
  polygon.resize(n);
  for (auto& p : polygon) cin >> p.x >> p.y;
  cin >> q;
  while (q--) {
    Point p;
    cin >> p.x >> p.y;

    if (on_polygon_boundary(p)) {
      cout << "ON" << endl;
    } else if (inside_polygon(p)) {
      cout << "IN" << endl;
    } else {
      cout << "OUT" << endl;
    }
  }
}
