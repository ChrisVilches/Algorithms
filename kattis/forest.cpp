#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-7

struct Point {
  double x, y;
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  double cross(const Point p) const { return x * p.y - y * p.x; }
  double magnitude() const { return hypot(x, y); }
  Point normalize() const { return {x / magnitude(), y / magnitude()}; }
  Point rot_ccw() const { return {-y, x}; }
  Point scale(const double f) const { return {x * f, y * f}; }
  bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
};

struct Segment {
  Point p, q;
  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }

  pair<bool, Point> intersect_non_collinear(const Segment& s) const {
    const bool o1 = orientation(p, q, s.p) * orientation(p, q, s.q) < 0;
    const bool o2 = orientation(s.p, s.q, p) * orientation(s.p, s.q, q) < 0;
    return o1 && o2 ? make_pair(true, intersection_point(s)) : make_pair(false, Point{});
  }

 private:
  int orientation(const Point& p, const Point& q, const Point& r) const {
    double val = (q - p).cross(r - p);
    if (fabs(val) < EPS) return 0;
    return val > 0 ? 1 : -1;
  }

  Point intersection_point(const Segment& s) const {
    const double factor = (s.q - s.p).cross(p - s.p) / (q - p).cross(s.q - s.p);
    return scale(factor).q;
  }
};

bool point_inside_polygon(const Point& p, const vector<Point>& polygon) {
  const int n = polygon.size();
  for (int i = 0; i < (int)polygon.size(); i++)
    if ((polygon[(i + 1) % n] - polygon[i]).cross(p - polygon[i]) <= 0) return false;

  return true;
}

Point point_set_centroid(const vector<Point>& points) {
  Point centroid{0, 0};

  for (const Point& p : points) {
    centroid.x += p.x / points.size();
    centroid.y += p.y / points.size();
  }

  return centroid;
}

vector<Point> sort_vertices(vector<Point> polygon_vertices) {
  const Point centroid = point_set_centroid(polygon_vertices);
  for (Point& p : polygon_vertices) p = p - centroid;
  sort(polygon_vertices.begin(), polygon_vertices.end());
  for (Point& p : polygon_vertices) p = p + centroid;
  return polygon_vertices;
}

vector<Point> polygon_intersection(const vector<Point>& p1, const vector<Point>& p2) {
  vector<Point> result;

  for (const Point& p : p1)
    if (point_inside_polygon(p, p2)) result.push_back(p);

  for (const Point& p : p2)
    if (point_inside_polygon(p, p1)) result.push_back(p);

  for (int i = 0; i < (int)p1.size(); i++) {
    for (int j = 0; j < (int)p2.size(); j++) {
      const Segment edge1{p1[i], p1[(i + 1) % (int)p1.size()]};
      const Segment edge2{p2[j], p2[(j + 1) % (int)p2.size()]};
      const auto [intersect, point] = edge1.intersect_non_collinear(edge2);
      if (intersect) result.push_back(point);
    }
  }

  return sort_vertices(result);
}

double polygon_area(const vector<Point>& polygon) {
  double total = 0;

  for (int i = 0; i < (int)polygon.size(); i++)
    total += polygon[i].cross(polygon[(i + 1) % (int)polygon.size()]);

  return fabs(total / 2);
}

vector<Point> build_line_polygon(const Point a, const Point b, const double d) {
  const Point dir = (b - a).normalize();
  const Point p = a + dir.scale(1e6);
  const Point q = a - dir.scale(1e6);
  const Point w = dir.rot_ccw().scale(d);

  return {p + w, q + w, q - w, p - w};
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
    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> d;
    const Point o{0, 0};
    vector<Point> line = build_line_polygon(a, b, d);
    double ans = 0;

    const double total_area = polygon_area(polygon);

    for (int i = 0; i < N; i++) {
      const Point p = polygon[i];
      const Point q = polygon[(i + 1) % N];
      const double sign = p.cross(q) > 0 ? 1 : -1;

      vector<Point> triangle{o, p, q};
      vector<Point> intersection = polygon_intersection(line, triangle);
      ans += sign * fabs(polygon_area(intersection));
    }

    cout << fixed << setprecision(9) << total_area - fabs(ans) << endl;
  }
}
