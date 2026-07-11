#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  int cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
};

int main() {
  int n;
  while (cin >> n) {
    vector<Point> points(n);
    for (Point& p : points) cin >> p.x >> p.y;

    int a, b;
    int ans = 0;

    for (int i = 0; i < n; i++) {
      vector<Point> centered;
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        centered.emplace_back(points[j] - points[i]);
      }

      for (const Point p : centered) {
        a = 0;
        b = 0;

        for (const Point q : centered) {
          const int area = p.cross(q);
          if (area >= 0) {
            a = max(a, area);
          } else {
            b = max(b, -area);
          }
        }

        if (a > 0 && b > 0) {
          ans = max(ans, a + b);
        }
      }
    }

    cout << fixed << setprecision(9) << ans / 2.0 << endl;
  }
}
