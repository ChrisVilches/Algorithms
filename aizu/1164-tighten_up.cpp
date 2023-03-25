#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  bool operator==(const Point p) const { return x == p.x && y == p.y; }
  Point rot_ccw(const double t) const {
    return {x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)};
  }
  double cross(const Point p) const { return x * p.y - y * p.x; }
  Point scale(const double f) const { return {x * f, y * f}; }
  double dist(const Point p) const { return hypot(x - p.x, y - p.y); }
};

struct Segment {
  Point p, q;
  double length() const { return p.dist(q); }
  bool operator==(Segment s) const { return p == s.p && q == s.q; }

  pair<bool, Point> intersect_single_point(const Segment s) const {
    return {intersect(s), intersection_point(s)};
  }

  bool intersect(const Segment& s) const {
    return (orientation(p, q, s.p) * orientation(p, q, s.q) <= 0) &&
           (orientation(s.p, s.q, p) * orientation(s.p, s.q, q) <= 0);
  }

 private:
  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }
  short orientation(const Point o, const Point a, const Point b) const {
    const double cross = (a - o).cross(b - o);
    return cross < 0 ? -1 : cross > 0;
  }

  Point intersection_point(const Segment& s) const {
    const double factor = (s.q - s.p).cross(p - s.p) / (q - p).cross(s.q - s.p);
    return scale(factor).q;
  }
};

int N, M;
vector<Point> polyline;
vector<Point> pins;
vector<Segment> path;

vector<vector<double>> memo;

int find_furthest_path_idx(const Segment s, const int from_path_idx) {
  int i = from_path_idx;
  if (!s.intersect(path[i])) return -1;

  double prev_dist = DBL_MIN;

  for (; i < (int)path.size(); i++) {
    const auto [intersects, point] = s.intersect_single_point(path[i]);

    if (intersects && prev_dist <= s.p.dist(point)) {
      prev_dist = s.p.dist(point);
    } else {
      break;
    }
  }

  return i;
}

double dp(const int pin_idx, const int path_idx) {
  if (path_idx == -1) return DBL_MAX;
  if (path_idx == (int)path.size()) return pins[pin_idx].dist(polyline.back());
  if (memo[pin_idx][path_idx] > -1) return memo[pin_idx][path_idx];

  double res = DBL_MAX;

  for (int i = 0; i <= M; i++) {
    const Segment movement{pins[pin_idx], pins[i]};
    res = min(res, movement.length() + dp(i, find_furthest_path_idx(movement, path_idx)));
  }

  return memo[pin_idx][path_idx] = res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N >> M && N > 0) {
    polyline.resize(N);
    pins.resize(M);
    path.clear();
    for (Point& p : polyline) cin >> p.x >> p.y;
    for (Point& p : pins) cin >> p.x >> p.y;
    for (Point& p : polyline) p = p.rot_ccw(0.00001);
    for (Point& p : pins) p = p.rot_ccw(0.00001);

    for (int i = 0; i < N - 1; i++) {
      const Segment s{polyline[i], polyline[i + 1]};

      vector<pair<double, Segment>> intersections;

      for (const Point pin : pins) {
        const Segment above{pin, {pin.x, 2000}};
        const Segment below{pin, {pin.x, -2000}};
        const auto [intersects_above, point_above] = s.intersect_single_point(above);
        const auto [intersects_below, point_below] = s.intersect_single_point(below);

        if (intersects_above) intersections.emplace_back(s.p.dist(point_above), above);
        if (intersects_below) intersections.emplace_back(s.p.dist(point_below), below);
      }

      sort(intersections.begin(), intersections.end(),
           [](const auto a, const auto b) { return a.first < b.first; });

      for (const auto& [_, s] : intersections) {
        if (!path.empty() && path.back() == s) {
          path.pop_back();
        } else {
          path.push_back(s);
        }
      }
    }

    pins.push_back(polyline.back());
    pins.push_back(polyline.front());

    memo.assign(pins.size(), vector<double>(path.size(), -1));

    cout << fixed << setprecision(10) << dp(M + 1, 0) << endl;
  }
}
