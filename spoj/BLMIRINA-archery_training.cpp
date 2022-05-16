#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

const ld EPS = 1e-9;

struct Point {
  ld x, y;

  inline ld magnitude() const { return hypot(x, y); }
};

array<Point, 2> points_of_tangency_from_origin(const Point& center, const ld radius) {
  const ld a = radius;
  const ld b = center.magnitude();
  const ld th = acos(a / b);
  const ld d = atan2(-center.y, -center.x);
  const ld d1 = d + th, d2 = d - th;

  return array<Point, 2>{Point{center.x + a * cos(d1), center.y + a * sin(d1)},
                         Point{center.x + a * cos(d2), center.y + a * sin(d2)}};
}

Point calculate(const ld x, const ld y, const ld r) {
  const array<Point, 2> points = points_of_tangency_from_origin({x, y}, r);

  const Point a = points[0];
  const Point b = points[1];

  return a.x < b.x ? a : b;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    ld x, y, r;
    cin >> x >> y >> r;

    const Point ans = calculate(x, y, r);

    cout << fixed << setprecision(6) << ans.x << " " << ans.y << endl;
  }
}
