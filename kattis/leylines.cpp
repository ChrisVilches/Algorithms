#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  Point rot_ccw(double t) const {
    return {x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)};
  }
  double cross(const Point& p) const { return x * p.y - y * p.x; }
  bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
  double magnitude() const { return hypot(x, y); }
  Point reflection() const { return {-x, -y}; }
};

int N;
double T;

int count(const vector<Point>& points) {
  int curr = 0;

  vector<pair<Point, int>> events;

  for (const Point& p : points) {
    curr += p.is_above() && p.y <= T;

    events.push_back({p, -1});
    events.push_back({p.reflection(), 1});

    if (p.magnitude() >= T) {
      const double angle = asin(T / p.magnitude());

      events.push_back({p.rot_ccw(-angle), 1});
      events.push_back({p.rot_ccw(angle).reflection(), -1});
    }
  }

  sort(events.begin(), events.end());

  int ans = curr;

  for (const auto& [_, d] : events) {
    curr += d;
    ans = max(ans, curr);
  }

  return ans;
}

int main() {
  while (cin >> N >> T) {
    vector<Point> points(N);

    for (Point& p : points) cin >> p.x >> p.y;

    T += 1e-8;

    int ans = 0;

    for (int i = 0; i < N; i++) {
      vector<Point> centered_points;

      for (int j = 0; j < N; j++)
        if (i != j) centered_points.push_back(points[j] - points[i]);

      ans = max(ans, count(centered_points));
    }

    cout << ans + 1 << endl;
  }
}
