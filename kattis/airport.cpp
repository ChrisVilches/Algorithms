#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  double cross(const Point& p) const { return x * p.y - y * p.x; }
  double operator*(const Point& p) const { return x * p.x + y * p.y; }
  Point negate() const { return {-x, -y}; };
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
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
    return o1 && o2 ? make_pair(true, intersection_point(s)) : make_pair(false, Point{});
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
  if (orientation(s.p, s.q, v1) != 0 || (s.q - s.p) * (v1 - s.p) < 0) return false;

  const Point v0 = i == 0 ? polygon.back() : polygon[i - 1];
  const Point v2 = polygon[(i + 1) % polygon.size()];

  const double edges_ang = angle(v1, v0, v2);
  double p_ang = angle(v1, v0, s.p);
  double q_ang = angle(v1, v0, s.q);

  if (p_ang > q_ang) swap(p_ang, q_ang), swap(s.p, s.q);

  return orientation(v0, v1, s.p) == 0 ? (0 < q_ang && q_ang < edges_ang)
                                       : p_ang < edges_ang;
}

Point first_collision(const vector<Point>& polygon, const Point& p, const Point& dir) {
  const Segment ray = Segment{p, p + dir}.scale(10'000'000);

  Point res = ray.q;

  for (int i = 0; i < (int)polygon.size(); i++) {
    if (vertex_intersection(polygon, ray, i))
      if (p.dist(polygon[i]) < p.dist(res)) res = polygon[i];

    const Segment edge{polygon[i], polygon[(i + 1) % polygon.size()]};
    const auto [intersects, point] = edge.intersect_non_collinear(ray);
    if (intersects && p.dist(point) < p.dist(res)) res = point;
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N) {
    vector<Point> polygon(N);
    for (Point& p : polygon) cin >> p.x >> p.y;

    double ans = 0;

    for (int i = 0; i < (int)polygon.size(); i++) {
      for (int j = i + 1; j < (int)polygon.size(); j++) {
        const Point p = polygon[i];
        const Point dir = polygon[j] - polygon[i];

        const Point endpoint1 = first_collision(polygon, p, dir);
        const Point endpoint2 = first_collision(polygon, p, dir.negate());

        ans = max(ans, endpoint1.dist(endpoint2));
      }
    }

    cout << fixed << setprecision(9) << ans << endl;
  }
}
