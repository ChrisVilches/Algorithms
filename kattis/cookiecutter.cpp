#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  double cross(const Point p) const { return x * p.y - y * p.x; }
};

double polygon_area(const vector<Point>& polygon) {
  const int n = polygon.size();
  double total = 0;

  for (int i = n - 1, j = 0; j < n; i = j++) {
    const Point p = polygon[i];
    const Point q = polygon[j];
    total += p.cross(q);
  }

  return total / 2;
}

vector<Point> polygon_scale(vector<Point> polygon, const double f) {
  for (auto& p : polygon) {
    p.x *= f;
    p.y *= f;
  }

  return polygon;
}

int main() {
  int n;
  double a;
  cin >> n;
  vector<Point> polygon(n);
  for (auto& p : polygon) cin >> p.x >> p.y;
  cin >> a;

  double min_x = 1e8;
  double min_y = 1e8;

  for (const auto p : polygon) {
    min_x = min(min_x, p.x);
    min_y = min(min_y, p.y);
  }

  for (auto& p : polygon) {
    p.x -= min_x;
    p.y -= min_y;
  }

  double lo = 0;
  double hi = 1e8;

  for (int iter = 0; iter < 150; iter++) {
    const double mid = (lo + hi) / 2;

    const vector<Point> scaled = polygon_scale(polygon, mid);

    const double area = polygon_area(scaled);

    if (area < a) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  for (const auto p : polygon_scale(polygon, lo)) {
    cout << fixed << setprecision(8) << p.x << ' ' << p.y << endl;
  }
}
