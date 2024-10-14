#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  int operator*(const Point p) const { return x * p.x + y * p.y; }
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  Point negate() const { return {-x, -y}; }
  int cross(const Point p) const { return x * p.y - y * p.x; }
  double dist(const Point p) const { return hypot(x - p.x, y - p.y); }
  double segment_dist(const Point p, const Point q) const {
    const Point r = *this;
    if ((q - p) * (r - p) <= 0) return p.dist(r);
    if ((p - q) * (r - q) <= 0) return q.dist(r);
    return fabs((q - p).cross(r - p)) / p.dist(q);
  }
};

const Point origin{0, 0};
const double EPS = 1e-6;

array<Point, 4> minkowski(const array<Point, 2>& edge1, const array<Point, 2>& edge2) {
  int k = 0;
  array<Point, 4> res;

  for (const Point p : edge1) {
    for (const Point q : edge2) {
      res[k++] = p + q;
    }
  }

  const Point o = res.front();
  sort(res.begin() + 1, res.end(),
       [o](const Point p, const Point q) { return (p - o).cross(q - o) > 0; });

  return res;
}

bool point_inside_polygon(const array<Point, 4>& polygon, const Point r) {
  for (int i = 3, j = 0; j < 4; i = j++) {
    const Point p = polygon[i];
    const Point q = polygon[j];
    if ((q - p).cross(r - p) < 0) return false;
    if (r.segment_dist(p, q) < EPS) return true;
  }

  return true;
}

pair<double, double> rotation_range(const array<Point, 4>& polygon, const Point center) {
  double a = 0;
  double b = DBL_MAX;

  for (const Point p : polygon) {
    a = max(a, p.dist(center));
  }

  if (point_inside_polygon(polygon, center)) {
    return {a, 0};
  }

  for (int i = 3, j = 0; j < 4; i = j++) {
    b = min(b, center.segment_dist(polygon[i], polygon[j]));
  }

  return {a, b};
}

bool solve(const vector<Point>& A, const Point P, const vector<Point>& B, const Point Q) {
  const int n = A.size(), m = B.size();
  const Point center = P + Q;
  const double origin_dist = center.dist(origin);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      const auto sum = minkowski({A[i], A[(i + 1) % n]}, {B[j], B[(j + 1) % m]});
      const auto [a, b] = rotation_range(sum, center);

      if (a >= origin_dist && origin_dist >= b) {
        return true;
      }
    }
  }

  return false;
}

int main() {
  Point P, Q;
  int n, m;
  while (cin >> P.x >> P.y >> n) {
    vector<Point> A(n);
    for (auto& p : A) cin >> p.x >> p.y;
    cin >> Q.x >> Q.y >> m;
    vector<Point> B(m);
    for (auto& p : B) cin >> p.x >> p.y;
    for (auto& p : B) p = p.negate();
    cout << (solve(A, P, B, Q.negate()) ? "YES" : "NO") << endl;
  }
}
