#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  double cross(const Point& p) const { return x * p.y - y * p.x; }
  double operator*(const Point& p) const { return x * p.x + y * p.y; }
  double magnitude() const { return hypot(x, y); }
  bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }

  bool acute(const Point& p) const { return (*this * p) > 0; }
  bool deg0(const Point& p) const { return cross(p) == 0 && acute(p); }
};

struct Circle {
  double x, y, radius;

  bool touches_origin() const { return Point{x, y}.magnitude() <= radius; }

  pair<Point, Point> points_of_tangency_from_origin() const {
    const double a = radius;
    const double b = hypot(x, y);
    const double th = acos(a / b);
    const double d = atan2(-y, -x);
    const double d1 = d + th, d2 = d - th;
    return {{x + a * cos(d1), y + a * sin(d1)}, {x + a * cos(d2), y + a * sin(d2)}};
  }
};

void solve() {
  int N;
  cin >> N;
  vector<Circle> circles(N);

  for (Circle& c : circles) {
    cin >> c.x >> c.y >> c.radius;
  }

  int curr = 0;

  vector<pair<Point, bool>> events;

  for (const Circle& c : circles) {
    if (c.touches_origin()) {
      curr++;
      continue;
    }

    const auto [p1, p2] = c.points_of_tangency_from_origin();

    if (p2 < p1) curr++;

    events.emplace_back(p1, true);
    events.emplace_back(p2, false);
  }

  sort(events.begin(), events.end());

  int ans = 0;
  int subtract = 0;

  for (int i = 0; i < (int)events.size(); i++) {
    const auto [p1, enter] = events[i];
    const auto [p2, _] = events[(i + 1) % events.size()];

    if (enter) {
      curr++;
      ans = max(ans, curr);
    } else {
      subtract++;
    }

    if (p1.deg0(p2)) continue;

    curr -= subtract;
    subtract = 0;
  }

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  while (T--) solve();
}
