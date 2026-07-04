#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

struct Point {
  ll x, y;
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
};

int orientation(const Point o, const Point p, const Point q) {
  const ll x = (p - o).cross(q - o);
  return (x > 0) - (x < 0);
}

ld compute_intercept(const Point p, const Point q) {
  const ld slope = (p.y - q.y) / static_cast<ld>(p.x - q.x);
  return p.y - slope * p.x;
}

int main() {
  int n;
  while (cin >> n) {
    vector<Point> points(n);
    for (Point& p : points) cin >> p.x >> p.y;

    vector<Point> hull;

    ld ans = -1;

    for (const Point p : points) {
      while (hull.size() > 1 && orientation(hull[hull.size() - 2], hull.back(), p) == 1) {
        ans = max(ans, compute_intercept(hull[hull.size() - 2], hull.back()));
        hull.pop_back();
      }

      hull.emplace_back(p);
    }

    for (size_t i = 0; i < hull.size() - 1; i++) {
      const Point p = hull[i];
      const Point q = hull[i + 1];
      ans = max(ans, compute_intercept(p, q));
    }

    if (ans < 0) {
      cout << -1 << endl;
    } else {
      cout << fixed << setprecision(9) << ans << endl;
    }
  }
}
