#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  double dist2() const { return *this * *this; }
  double cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  double operator*(const Point p) const { return x * p.x + y * p.y; }
  Point scale(const double f) const { return {x * f, y * f}; }
};

double angle(const Point a, const Point b) { return atan2(a.cross(b), a * b); }

double sector_circle(const Point p, const Point q, const double r) {
  return angle(p, q) * (r * r) / 2;
}

vector<Point> circle_intersections(const Point p, const Point q, const double r) {
  const Point dir = q - p;

  const double a = dir * dir;
  const double b = 2 * (p * dir);
  const double c = p * p - r * r;

  const double discriminant = b * b - 4 * a * c;

  vector<Point> intersections;

  for (int i = -1; i <= 1 && discriminant >= 0; i += 2) {
    const double t = (-b + i * sqrt(discriminant)) / (2 * a);

    if (0 <= t && t <= 1) intersections.emplace_back(p + dir.scale(t));
  }

  return intersections;
}

double triangle(const Point p, const Point q) { return p.cross(q) / 2; }

double calculate_area(const Point p, const Point q, const double r) {
  const bool p_inside = r * r >= p.dist2();
  const bool q_inside = r * r >= q.dist2();

  if (p_inside && q_inside) return triangle(p, q);

  const vector<Point> intersections = circle_intersections(p, q, r);

  if (intersections.empty()) return sector_circle(p, q, r);

  const Point inter0 = intersections.front();
  const Point inter1 = intersections.back();

  if (p_inside && !q_inside) return triangle(p, inter0) + sector_circle(inter0, q, r);

  if (!p_inside && q_inside) return sector_circle(p, inter0, r) + triangle(inter0, q);

  return sector_circle(p, inter0, r) + triangle(inter0, inter1) +
         sector_circle(inter1, q, r);
}

int main() {
  int n;
  double r;

  while (cin >> n >> r) {
    vector<Point> polygon(n);
    for (auto& p : polygon) cin >> p.x >> p.y;

    double area = 0;

    for (int i = n - 1, j = 0; j < n; i = j++) {
      const Point p = polygon[i];
      const Point q = polygon[j];

      if (p.cross(q) > 0) {
        area += calculate_area(p, q, r);
      } else {
        area -= calculate_area(q, p, r);
      }
    }

    cout << fixed << setprecision(9) << fabs(area) << endl;
  }
}
