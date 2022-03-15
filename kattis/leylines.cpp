#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

struct Point {
  ld x, y;
  Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
  Point rot_ccw(ld t) const {
    return Point{x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)};
  }
  ld cross(const Point& p) const { return x * p.y - y * p.x; }
  bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
  inline ld magnitude() const { return hypot(x, y); }
  inline Point reflection() const { return Point{-x, -y}; }
};

int N;
ld T;
bool inside[3007];

int count(vector<Point>& points) {
  int curr = 0;

  memset(inside, 0, sizeof inside);
  vector<pair<Point, int>> events;

  for (int i = 0; i < (int)points.size(); i++) {
    const Point& p = points[i];

    if (p.is_above() && p.y <= T) {
      inside[i] = true;
      curr++;
    }

    events.push_back({p, i});
    events.push_back({p.reflection(), i});

    if (p.magnitude() >= T) {
      ld angle = asin(T / p.magnitude());

      events.push_back({p.rot_ccw(-angle), i});
      events.push_back({p.rot_ccw(angle).reflection(), i});
    }
  }

  sort(events.begin(), events.end());

  int ans = curr;

  for (const auto& [_, idx] : events) {
    curr += inside[idx] ? -1 : 1;
    inside[idx] = !inside[idx];

    ans = max(ans, curr);
  }

  return ans;
}

int main() {
  while (cin >> N >> T) {
    vector<Point> points(N);

    for (int i = 0; i < N; i++) cin >> points[i].x >> points[i].y;

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
