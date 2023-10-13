#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  double cross(const Point p) const { return x * p.y - y * p.x; }
};

double polygon_area(const vector<Point>& polygon) {
  const int n = polygon.size();
  double total = 0;

  for (int j = 0, i = n - 1; j < n; i = j++) {
    total += polygon[i].cross(polygon[j]);
  }

  return total / 2;
}

Point polygon_centroid(const vector<Point>& polygon) {
  const int n = polygon.size();
  const double area = polygon_area(polygon);
  Point c{0, 0};
  for (int j = 0, i = n - 1; j < n; i = j++) {
    const Point p = polygon[i];
    const Point q = polygon[j];
    c.x += (p.x + q.x) * p.cross(q);
    c.y += (p.y + q.y) * p.cross(q);
  }

  c.x /= area * 6;
  c.y /= area * 6;
  return c;
}

int main() {
  int N;
  while (cin >> N) {
    vector<Point> polygon(N);
    for (auto& p : polygon) cin >> p.x >> p.y;

    double left_x = DBL_MAX;
    double right_x = -DBL_MAX;

    for (const auto p : polygon) {
      if (p.y != 0) continue;
      left_x = min(left_x, p.x);
      right_x = max(right_x, p.x);
    }

    const double area = polygon_area(polygon);
    const Point c = polygon_centroid(polygon);

    const auto solve = [&](const double x) -> double {
      const double x1 = c.x;
      const double x2 = polygon[0].x;
      const double m1 = fabs(area);
      return m1 * (x - x1) / (x2 - x);
    };

    const double x = polygon[0].x;

    const bool both_right = right_x <= x && right_x <= c.x;
    const bool both_left = x <= left_x && c.x <= left_x;

    const bool opposite_sides =
        (c.x < left_x && right_x < x) || (x < left_x && right_x < c.x);

    const bool mass_center_contained = left_x <= c.x && c.x <= right_x;
    const bool crane_weight_contained = left_x <= x && x <= right_x;

    double lo = 0;
    double hi = INFINITY;

    if (both_left || both_right) {
      cout << "unstable" << endl;
      continue;
    } else if (mass_center_contained && !crane_weight_contained) {
      lo = 0;
      hi = solve(x < left_x ? left_x : right_x);
    } else if (!mass_center_contained && crane_weight_contained) {
      lo = solve(right_x < c.x ? right_x : left_x);
      hi = INFINITY;
    } else if (opposite_sides) {
      lo = solve(c.x < x ? left_x : right_x);
      hi = solve(c.x < x ? right_x : left_x);
    }

    cout << fixed << setprecision(0) << floor(lo) << " .. " << ceil(hi) << endl;
  }
}
