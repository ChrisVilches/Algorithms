#include <bits/stdc++.h>
using namespace std;

const double INF = 1e15;

struct Point {
  double x, y;
  Point rot_ccw(const double t) const {
    return {x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)};
  }
  double dist(const Point p) const { return hypot(x - p.x, y - p.y); }
};

struct Boat {
  Point p, v;

  static Boat from_stdin() {
    Boat b;
    double d, s;
    cin >> b.p.x >> b.p.y >> d >> s;
    b.v = Point{0, s}.rot_ccw(-d * M_PI / 180);
    return b;
  }
};

void solve() {
  int n;
  double r;
  cin >> n >> r;

  vector<Boat> boats;

  for (int i = 0; i < n; i++) boats.emplace_back(Boat::from_stdin());

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (boats[i].p.dist(boats[j].p) <= r) {
        cout << 0 << endl;
        return;
      }
    }
  }

  double ans = INF;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      const Point p = boats[i].p;
      const Point q = boats[j].p;
      const Point v = boats[i].v;
      const Point w = boats[j].v;

      const double dx = p.x - q.x;
      const double dy = p.y - q.y;
      const double dvx = v.x - w.x;
      const double dvy = v.y - w.y;

      const double a = dvx * dvx + dvy * dvy;
      const double b = 2 * (dx * dvx + dy * dvy);
      const double c = dx * dx + dy * dy - r * r;

      const double discriminant = b * b - 4 * a * c;

      if (discriminant < 0) continue;

      const double t0 = (-b + sqrt(discriminant)) / (2 * a);
      const double t1 = (-b - sqrt(discriminant)) / (2 * a);

      for (const double t : array<double, 2>{t0, t1}) {
        if (t < 0) continue;
        ans = min(ans, t);
      }
    }
  }

  if (ans == INF) {
    cout << "No collision." << endl;
  } else {
    cout << (long long)round(ans) << endl;
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) solve();
}
