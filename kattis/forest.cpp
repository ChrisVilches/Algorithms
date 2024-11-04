#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  double cross(const Point p) const { return x * p.y - y * p.x; }
  double magnitude() const { return hypot(x, y); }
  Point normalize() const { return {x / magnitude(), y / magnitude()}; }
  Point rot_ccw() const { return {-y, x}; }
  Point scale(const double f) const { return {x * f, y * f}; }
};

int orientation(const Point o, const Point p, const Point q) {
  const double x = (p - o).cross(q - o);
  return (x > 0) - (x < 0);
}

struct Segment {
  Point p, q;
  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }

  optional<Point> intersect_adhoc(const Segment s) const {
    if (orientation(p, q, s.p) * orientation(p, q, s.q) == 1) return nullopt;
    const double div = (q - p).cross(s.q - s.p);
    if (div == 0) return nullopt;
    const double factor = (s.q - s.p).cross(p - s.p) / div;
    return scale(factor).q;
  }
};

double polygon_area(const vector<Point>& polygon) {
  double total = 0;

  for (int i = 0; i < (int)polygon.size(); i++)
    total += polygon[i].cross(polygon[(i + 1) % (int)polygon.size()]);

  return fabs(total / 2);
}

vector<Point> intersection_adhoc(const Point a, const Point b, const double d,
                                 const vector<Point>& polygon) {
  vector<Point> res;

  const Point dir = (b - a).normalize();
  const Point point1 = a + dir.rot_ccw().scale(d);
  const Point point2 = a + dir.rot_ccw().scale(-d);
  const array<Segment, 2> edges{
      Segment{point1, point1 - dir},
      Segment{point2, point2 + dir},
  };

  for (const Point p : polygon) {
    if (all_of(edges.begin(), edges.end(),
               [p](const auto e) { return orientation(e.p, e.q, p) == 1; })) {
      res.emplace_back(p);
    }
  }

  for (const Segment e : edges) {
    const int n = polygon.size();
    for (int i = n - 1, j = 0; j < n; i = j++) {
      const optional<Point> point = e.intersect_adhoc({polygon[i], polygon[j]});
      if (point.has_value()) res.emplace_back(point.value());
    }
  }

  if (!res.empty()) {
    sort(res.begin() + 1, res.end(), [&](const Point p, const Point q) {
      return (p - res.front()).cross(q - res.front()) > 0;
    });
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  double d;
  while (cin >> N) {
    vector<Point> polygon(N);
    for (auto& p : polygon) cin >> p.x >> p.y;
    Point a, b;
    cin >> a.x >> a.y >> b.x >> b.y >> d;
    const Point o{0, 0};

    const double total_area = polygon_area(polygon);
    double ans = 0;

    for (int i = N - 1, j = 0; j < N; i = j++) {
      const Point p = polygon[i];
      const Point q = polygon[j];

      const vector<Point> triangle{o, p, q};
      const vector<Point> intersection = intersection_adhoc(a, b, d, triangle);
      ans += orientation(o, p, q) * polygon_area(intersection);
    }

    cout << fixed << setprecision(9) << total_area - fabs(ans) << endl;
  }
}
