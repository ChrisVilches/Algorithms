#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  double cross(const Point p) const { return x * p.y - y * p.x; }
  double operator*(const Point p) const { return x * p.x + y * p.y; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point scale(const double f) const { return {x * f, y * f}; }
};

vector<Point> solve(const double a, const double b, const double c, const Point p,
                    const Point q) {
  const double discriminant = (b * b) - (4 * a * c);
  if (discriminant < 0) return {};
  const double t[]{(-b - sqrt(discriminant)) / (2 * a),
                   (-b + sqrt(discriminant)) / (2 * a)};

  return {p + (q - p).scale(clamp(t[0], 0.0, 1.0)),
          p + (q - p).scale(clamp(t[1], 0.0, 1.0))};
}

double angle(const Point a, const Point b) { return atan2(a.cross(b), a * b); }

double area_sector_circle(const double r, const Point p, const Point q) {
  return angle(p, q) * r * r / 2;
}

double area(const double r, const Point p, const Point q) {
  const Point dir = q - p;
  const double a = dir * dir;
  const double b = p * dir * 2;
  const double c = p * p - r * r;
  const vector<Point> sols = solve(a, b, c, p, q);

  if (sols.empty()) return area_sector_circle(r, p, q);

  return area_sector_circle(r, p, sols[0]) + (sols[0].cross(sols[1]) / 2) +
         area_sector_circle(r, sols[1], q);
}

int main() {
  int n;
  double r;

  while (cin >> n >> r) {
    vector<Point> points(n);
    for (auto& p : points) cin >> p.x >> p.y;

    double total = 0;

    for (int j = 0, i = n - 1; j < n; i = j++) {
      total += area(r, points[i], points[j]);
    }

    cout << fixed << setprecision(9) << total << endl;
  }
}
