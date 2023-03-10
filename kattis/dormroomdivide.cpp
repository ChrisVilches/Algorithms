#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  double cross(const Point& p) const { return x * p.y - y * p.x; }
  Point scale(const double f) const { return {x * f, y * f}; }
};

int N;
vector<Point> polygon;

double area(const int a, const int b, const int c) {
  const Point p = polygon[a];
  const Point q = polygon[b];
  const Point r = polygon[c];
  return fabs((p - q).cross(r - q)) * 0.5;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N) {
    polygon.resize(N);
    for (Point& p : polygon) cin >> p.x >> p.y;

    double full_area = 0;
    for (int i = 2; i < N; i++) full_area += area(0, i - 1, i);
    const double target = full_area * 0.5;

    double first_part = 0;

    int i = 2;
    for (; i < N; i++) {
      const double add_area = area(0, i - 1, i);
      if (first_part + add_area >= target) break;
      first_part += add_area;
    }

    const double missing = (full_area / 2) - first_part;

    Point lo = polygon[i - 1];
    Point hi = polygon[i];
    const Point breakpoint = lo;
    Point mid{0, 0};

    for (int it = 0; it < 60; it++) {
      mid = lo + (hi - lo).scale(0.5);
      const double curr_area =
          fabs((breakpoint - polygon[0]).cross(mid - polygon[0])) / 2;

      if (curr_area == missing) {
        break;
      }

      if (curr_area > missing) {
        hi = mid;
      } else {
        lo = mid;
      }
    }

    cout << fixed << setprecision(8) << mid.x << " " << mid.y << endl;
  }
}
