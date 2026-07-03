#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
  ll x, y;
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  ll operator*(const Point p) const { return x * p.x + y * p.y; }
  bool first_half() const { return y > 0 || (y == 0 && x > 0); }
  bool operator<(const Point p) const {
    return first_half() != p.first_half() ? first_half() : cross(p) > 0;
  }
};

int main() {
  int n;
  while (cin >> n) {
    vector<Point> points;
    for (int i = 0; i < n; i++) {
      Point p;
      cin >> p.x >> p.y;
      if (p.x == 0 && p.y == 0) continue;
      points.emplace_back(p);
    }
    n = points.size();

    ll ans = 0;
    Point curr{0, 0};

    sort(points.begin(), points.end());

    for (int i = 0, j = 0; i < n; i++) {
      const Point p = points[i];

      while (j - i < n) {
        const Point q = points[j % n];

        if (p.cross(q) < 0) break;
        if (p.cross(q) == 0 && p * q < 0) break;

        curr = curr + q;
        ans = max(ans, curr * curr);
        j++;
      }

      curr = curr - p;
      ans = max(ans, curr * curr);
    }

    cout << fixed << setprecision(12) << sqrt(ans) << endl;
  }
}
