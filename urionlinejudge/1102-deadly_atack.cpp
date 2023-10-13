#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  double cross(const Point p) const { return x * p.y - y * p.x; }
  double operator*(const Point p) const { return x * p.x + y * p.y; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  Point scale(const double f) const { return {x * f, y * f}; }
  bool ccw(const Point p) const { return cross(p) >= 0; }
};

double angle(const Point a, const Point b) {
  double ang = atan2(a.cross(b), a * b);
  return ang < 0 ? ang + 2 * M_PI : ang;
}

double angle(const Point o, const Point a, const Point b) { return angle(a - o, b - o); }

pair<Point, Point> circle_intersections_from_origin(const Point center, const double r,
                                                    const Point dir) {
  const double a = 1;
  const double b = -2 * ((center.x * dir.x) + (center.y * dir.y));
  const double c = pow(center.x, 2) + pow(center.y, 2) - pow(r, 2);

  const double discriminant = (b * b) - (4 * a * c);
  const double t1 = (-b - sqrt(discriminant)) / (2 * a);
  const double t2 = (-b + sqrt(discriminant)) / (2 * a);
  return {dir.scale(t1), dir.scale(t2)};
}

double circular_segment_area(const Point center, const double r, const double ang) {
  return 0.5 * (ang - sin(ang)) * r * r;
}

pair<Point, Point> points_of_tangency_from_origin(const Point center, const double r) {
  const double dist = hypot(center.x, center.y);
  const double th = acos(r / dist);
  const double d = atan2(-center.y, -center.x);
  const double a = d + th;
  const double b = d - th;

  return {{center.x + r * cos(a), center.y + r * sin(a)},
          {center.x + r * cos(b), center.y + r * sin(b)}};
}

double compute_area(const Point tan1, const Point tan2, const Point dir1,
                    const Point dir2, const Point circle_center, const double r) {
  const auto [a, b] = circle_intersections_from_origin(circle_center, r, dir1);
  const auto [c, d] = circle_intersections_from_origin(circle_center, r, dir2);

  if (dir2.ccw(tan1) && tan2.ccw(dir1)) return 0;
  if (dir1.ccw(tan1) && tan2.ccw(dir2)) return M_PI * r * r;

  double ang1 = 0;
  double ang2 = 0;

  if (dir1.ccw(tan2) && tan2.ccw(dir2)) {
    ang1 = angle(circle_center, b, a);
    ang2 = 0;
  } else if (dir1.ccw(tan1) && tan1.ccw(dir2)) {
    ang1 = 2 * M_PI;
    ang2 = angle(circle_center, d, c);
  } else if (tan1.ccw(dir1) && dir2.ccw(tan2)) {
    ang1 = angle(circle_center, b, a);
    ang2 = angle(circle_center, d, c);
  }

  return circular_segment_area(circle_center, r, ang1) -
         circular_segment_area(circle_center, r, ang2);
}

int main() {
  double x, y, r, cx, cy, a, t;

  while (cin >> x >> y >> r >> cx >> cy >> a >> t && (x != 0 || y != 0 || r != 0)) {
    x -= cx;
    y -= cy;
    a = a * M_PI / 180;
    t = t * M_PI / 180;

    const Point dir1{cos(a - t / 2), sin(a - t / 2)};
    const Point dir2{cos(a + t / 2), sin(a + t / 2)};

    const Point circle_center{x, y};
    const auto [tan1, tan2] = points_of_tangency_from_origin(circle_center, r);

    const double ans = compute_area(tan1, tan2, dir1, dir2, circle_center, r);

    cout << fixed << setprecision(1) << ans << endl;
  }
}
