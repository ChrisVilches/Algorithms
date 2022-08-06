#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  double cross(const Point& p) const { return x * p.y - y * p.x; }
  double operator*(const Point& p) const { return x * p.x + y * p.y; }
  Point scale(const double f) const { return {x * f, y * f}; }
  double dist(const Point& p) const { return hypot(x - p.x, y - p.y); }
};

short orientation(const Point& o, const Point& a, const Point& b) {
  const double cross = (a - o).cross(b - o);
  return cross < 0 ? -1 : cross > 0;
}

struct Segment {
  Point p, q;

  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }

  pair<bool, Point> intersect_non_collinear(const Segment& s) const {
    const bool o1 = orientation(p, q, s.p) * orientation(p, q, s.q) < 0;
    const bool o2 = orientation(s.p, s.q, p) * orientation(s.p, s.q, q) < 0;
    return {o1 && o2, intersection_point(s)};
  }

 private:
  Point intersection_point(const Segment& s) const {
    const double factor = (s.q - s.p).cross(p - s.p) / (q - p).cross(s.q - s.p);
    return scale(factor).q;
  }
};

double angle(const Point& a, const Point& b) {
  const double x = atan2(a.cross(b), a * b);
  return x < 0 ? x + 2 * M_PI : x;
}

double angle(const Point& o, const Point& a, const Point& b) {
  return angle(a - o, b - o);
}

bool vertex_intersection(const vector<Point>& polygon, Segment s, const int i) {
  const Point v1 = polygon[i];
  if (orientation(s.p, s.q, v1) != 0) return false;

  const Point v0 = i == 0 ? polygon.back() : polygon[i - 1];
  const Point v2 = polygon[(i + 1) % polygon.size()];

  const double edges_ang = angle(v1, v0, v2);
  double p_ang = angle(v1, v0, s.p);
  double q_ang = angle(v1, v0, s.q);

  if (p_ang > q_ang) swap(p_ang, q_ang), swap(s.p, s.q);

  if (p_ang == 0) return q_ang < edges_ang;
  return p_ang < edges_ang && edges_ang <= q_ang;
}

bool is_ccw(const vector<Point>& polygon) {
  double total = 0;

  for (int i = 0; i < (int)polygon.size(); i++) {
    const Point& p = polygon[i];
    const Point& q = polygon[(i + 1) % polygon.size()];
    total += (q.x - p.x) * (q.y + p.y);
  }

  return total < 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;

  while (cin >> N >> M && N && M) {
    vector<Point> polygon(N);
    for (Point& p : polygon) cin >> p.x >> p.y;

    if (!is_ccw(polygon)) reverse(polygon.begin(), polygon.end());

    while (M--) {
      Segment line;
      cin >> line.p.x >> line.p.y;
      cin >> line.q.x >> line.q.y;

      line = line.scale(1e6);
      swap(line.p, line.q);
      line = line.scale(1e6);

      vector<Point> points;

      for (int i = 0; i < (int)polygon.size(); i++) {
        const Segment edge{polygon[i], polygon[(i + 1) % polygon.size()]};

        if (vertex_intersection(polygon, line, i)) points.push_back(polygon[i]);

        const auto [intersects, point] = edge.intersect_non_collinear(line);
        if (intersects) points.push_back(point);
      }

      sort(points.begin(), points.end(), [line](const Point& a, const Point& b) {
        return a.dist(line.p) < b.dist(line.p);
      });

      assert(points.size() % 2 == 0);

      double ans = 0;

      for (int i = 0; i < (int)points.size(); i += 2)
        ans += points[i].dist(points[i + 1]);

      cout << fixed << setprecision(3) << ans << endl;
    }
  }
}
