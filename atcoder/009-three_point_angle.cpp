#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
  ll x, y;
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  ll operator*(const Point p) const { return x * p.x + y * p.y; }
  bool first_half() const { return y > 0 || (y == 0 && x > 0); }
  bool operator<(const Point p) const {
    return first_half() != p.first_half() ? first_half() : cross(p) > 0;
  }
};

double angle(const Point a, const Point b) { return atan2(a.cross(b), a * b); }

int main() {
  int n;
  while (cin >> n) {
    vector<Point> points(n);
    for (Point& p : points) cin >> p.x >> p.y;

    double ans = 0;

    for (int c = 0; c < n; c++) {
      const Point center = points[c];
      vector<Point> centered;
      for (int i = 0; i < n; i++) {
        if (c == i) continue;
        centered.emplace_back(points[i] - center);
      }

      sort(centered.begin(), centered.end());

      for (int i = 0, j = 0; i < n - 1; i++) {
        const Point p = centered[i];

        while (true) {
          const Point next = centered[(j + 1) % (n - 1)];

          if (p.cross(next) < 0) break;
          if (p.cross(next) == 0 && p * next > 0) break;

          j++;
        }

        ans = max(ans, angle(p, centered[j % (n - 1)]));
      }
    }

    cout << fixed << setprecision(9) << ans * 180 / M_PI << endl;
  }
}
