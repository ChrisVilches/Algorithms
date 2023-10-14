#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld EPS = 1e-7;
inline bool equal(const ld a, const ld b) { return fabs(a - b) < EPS; }

struct Point {
  ld x, y;
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  ld magnitude() const { return hypot(x, y); }
  Point normalize() const { return scale(1 / magnitude()); }
  ld dist(const Point p) const { return (*this - p).magnitude(); }
  Point scale(const ld f) const { return {x * f, y * f}; }
};

struct PiecewiseFunction {
  PiecewiseFunction() {}
  PiecewiseFunction(const vector<Point>& points) {
    ld accum = 0;

    for (int i = 0; i < (int)points.size() - 1; i++) {
      fn.emplace_back(points[i], (points[i + 1] - points[i]).normalize());
      intervals.emplace_back(accum);
      accum += points[i].dist(points[i + 1]);
    }
    intervals.emplace_back(accum);
    fn.emplace_back(Point{NAN, NAN}, Point{NAN, NAN});
  }

  Point operator()(ld t) const {
    auto it = lower_bound(intervals.begin(), intervals.end(), t);
    if (it != intervals.begin()) it--;
    const ld t0 = *it;
    const auto [p, direction] = fn[it - intervals.begin()];
    return p + direction.scale(t - t0);
  };

  vector<ld> intervals;

 private:
  vector<pair<Point, Point>> fn;
};

vector<Point> path1, path2;
ld receive_time_limit;
PiecewiseFunction fn1, fn2;

ld find_receiver(const ld t) {
  ld lo = t;
  ld hi = receive_time_limit;
  const Point p = fn1(t);
  ld points_dist;

  if (equal(p.dist(fn2(t)), 0)) {
    return t;
  }

  for (int it = 0; it < 60; it++) {
    const ld mid = (lo + hi) / 2;
    const Point q = fn2(mid);
    points_dist = p.dist(q);
    if (points_dist > mid - t) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  if (equal(points_dist, lo - t)) return lo;
  return DBL_MAX;
}

ld find_sender(const ld t) {
  const Point q = fn2(t);
  ld lo = 0;
  ld hi = t;
  ld points_dist;

  for (int it = 0; it < 60; it++) {
    const ld mid = (lo + hi) / 2;
    const Point p = fn1(mid);
    points_dist = p.dist(q);
    if (points_dist < t - mid) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  return hi;
}

void solve() {
  ld ans = DBL_MAX;

  fn1 = PiecewiseFunction(path1);
  fn2 = PiecewiseFunction(path2);

  vector<ld> times = fn1.intervals;

  for (const ld t : fn2.intervals) {
    const ld inv = find_sender(t);
    if (!equal(inv, 0)) times.push_back(inv);
    receive_time_limit = t;
  }

  sort(times.begin(), times.end());

  for (int i = 0; i < (int)times.size() - 1; i++) {
    const ld t0 = times[i];
    const ld t1 = times[i + 1];
    if (equal(t0, t1)) continue;
    const ld t0_receive = find_receiver(t0);
    const ld t1_receive = find_receiver(t1);
    if (t0_receive > receive_time_limit) break;
    ans = min({ans, t0_receive - t0, t1_receive - t1});
    if (equal(t0_receive, t1_receive)) continue;
    if (equal(ans, 0)) break;

    const Point p1 = fn1(t0);
    const Point p2 = fn1(t1);
    const Point q1 = fn2(t0_receive);
    const Point q2 = fn2(t1_receive);

    const Point dir = q2 - q1;
    const ld dt = t1_receive - t0_receive;

    const auto solve_equation = [&](const ld t) -> ld {
      const Point p = p1 + (p2 - p1).scale((t - t0) / (t1 - t0));

      const ld u = dir.x / dt;
      const ld w = dir.y / dt;
      const ld f = q1.x - (u * t0_receive) - p.x;
      const ld g = q1.y - (w * t0_receive) - p.y;
      const ld b = (2 * f * u) + (2 * g * w) + (2 * t);
      const ld c = (f * f) + (g * g) - (t * t);
      const ld res = -c / b;
      if (res < t0_receive || t1_receive < res) return DBL_MAX;

      return res - t;
    };

    ld lo = t0;
    ld hi = t1;

    for (int it = 0; it < 50; it++) {
      const ld third = (hi - lo) / 3;
      const ld time1 = lo + third;
      const ld time2 = hi - third;

      if (solve_equation(time1) > solve_equation(time2)) {
        lo = time1;
      } else {
        hi = time2;
      }
    }

    ans = min(ans, solve_equation(lo));
  }

  if (ans > receive_time_limit) {
    cout << "impossible" << endl;
  } else {
    cout << fixed << setprecision(7) << ans << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  while (cin >> n) {
    path1.resize(n);
    for (auto& p : path1) cin >> p.x >> p.y;
    cin >> n;
    path2.resize(n);
    for (auto& p : path2) cin >> p.x >> p.y;

    solve();
  }
}
