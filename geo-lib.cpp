// Visualize geometric shapes using desmos
// Print several objects using `cerr << my_segment.to_desmos() << endl;`, then paste
// (multiple lines at once is allowed) on https://www.desmos.com/calculator?lang=ja

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Point {
  ll x, y;
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
};

ostream& operator<<(ostream& os, const Point p) {
  return os << "(" << p.x << ", " << p.y << ")";
}

struct Segment {
  Point p, q;

  string to_desmos() const {
    stringstream ss;
    ss << fixed << setprecision(6) << "\\left(\\left(1-t\\right)\\cdot" << p.x
       << "+t\\cdot" << q.x << ",\\left(1-t\\right)\\cdot" << p.y << "+t\\cdot" << q.y
       << "\\right)";
    return ss.str();
  }
};

struct Circle {
  Point center;
  long double radius;

  string to_desmos() const {
    stringstream ss;
    ss << "\\left(x-" << center.x << "\\right)^{2}+\\left(y-" << center.y
       << "\\right)^{2}=" << radius << "^{2}";
    return ss.str();
  }
};

string polygon_to_str(const vector<Point>& polygon) {
  stringstream ss;
  ss << fixed << setprecision(6);
  ss << "polygon(";
  for (size_t i = 0; i < polygon.size(); i++) {
    if (i > 0) ss << ", ";
    ss << polygon[i];
  }
  ss << ")";
  return ss.str();
}
