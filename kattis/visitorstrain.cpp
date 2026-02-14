#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  double cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point scale(const double f) const { return {x * f, y * f}; }
  double dist(const Point p) const { return hypot(x - p.x, y - p.y); }
};

using Rect = array<Point, 4>;

int orientation(const Point o, const Point p, const Point q) {
  const double x = (p - o).cross(q - o);
  return (x > 0) - (x < 0);
}

struct Segment {
  Point p, q;
  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }
  Segment invert() const { return {q, p}; }
  optional<Point> intersect_adhoc(const Segment s) const {
    if (orientation(p, q, s.p) * orientation(p, q, s.q) == 1) return nullopt;
    const double factor = (s.q - s.p).cross(p - s.p) / (q - p).cross(s.q - s.p);
    if (factor <= 0) return nullopt;
    return scale(factor).q;
  }
};

Segment find_tangent(const Rect dest, const Rect src, const int dir) {
  const int n = 4;
  for (int i = 0; i < n; i++) {
    const Point p0 = src[(i - 1 + n) % n];
    const Point p1 = src[i];
    const Point p2 = src[(i + 1) % n];

    for (int j = 0; j < n; j++) {
      const Point q0 = dest[(j - 1 + n) % n];
      const Point q1 = dest[j];
      const Point q2 = dest[(j + 1) % n];

      const int or1 = orientation(p1, q1, q2);
      const int or2 = orientation(p1, q1, q0);
      const int or3 = orientation(p1, q1, p2);
      const int or4 = orientation(p1, q1, p0);

      if (or1 == dir || or2 == dir) continue;
      if (or3 == -dir || or4 == -dir) continue;
      return {p1, q1};
    }
  }
  assert(false);
}

vector<Point> adhoc_intersection(const Segment s, const Segment ray1,
                                 const Segment ray2) {
  vector<Point> res;

  for (const Point p : {s.p, s.q}) {
    const array<Segment, 3> edges{ray1, {ray2.p, ray1.p}, ray2.invert()};
    if (all_of(edges.begin(), edges.end(),
               [p](const auto e) { return orientation(e.p, e.q, p) == 1; })) {
      res.emplace_back(p);
    }
  }

  for (const Segment r : {ray1, ray2}) {
    const optional<Point> point = r.intersect_adhoc(s);
    if (point.has_value()) res.emplace_back(point.value());
  }

  return res;
}

double solve(const Segment rail, const vector<Rect>& rectangles) {
  vector<pair<double, int>> events;

  for (size_t i = 1; i < rectangles.size(); i++) {
    const Segment tan1 = find_tangent(rectangles[0], rectangles[i], -1);
    const Segment tan2 = find_tangent(rectangles[0], rectangles[i], 1);

    const vector<Point> points = adhoc_intersection(rail, tan1.scale(-1), tan2.scale(-1));

    if (points.size() == 2) {
      const double a = rail.p.dist(points.front());
      const double b = rail.p.dist(points.back());
      events.emplace_back(min(a, b), 1);
      events.emplace_back(max(a, b), -1);
    }
  }

  sort(events.begin(), events.end());

  double obscured = 0;
  double prev_dist = 0;
  int curr = 0;
  for (const auto& [dist, d] : events) {
    if (curr == 0) prev_dist = dist;
    curr += d;
    if (curr == 0) obscured += dist - prev_dist;
  }

  return rail.p.dist(rail.q) - obscured;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    Segment rail;
    cin >> rail.p.x >> rail.p.y >> rail.q.x >> rail.q.y;
    vector<Rect> rectangles(n);
    for (auto& rect : rectangles)
      for (auto& p : rect) cin >> p.x >> p.y;

    cout << fixed << setprecision(8) << solve(rail, rectangles) << endl;
  }
}
