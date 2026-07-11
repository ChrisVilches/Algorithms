#include <bits/stdc++.h>
using namespace std;

struct Point {
  using ll = long long;
  ll x, y;
  int type;
  Point operator-(const Point p) const { return {x - p.x, y - p.y, type}; }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
  Point to_above() const { return is_above() ? *this : Point{-x, -y, type}; }
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  bool operator<(const Point p) const { return to_above().cross(p.to_above()) > 0; }
};

int sweep(const vector<Point>& points) {
  array<int, 2> ingredients{0, 0};

  for (const Point p : points) {
    if (p.is_above()) ingredients[p.type]++;
  }

  int res = 0;

  for (int sgn = -1; sgn <= 1; sgn += 2) {
    for (size_t i = 0; i < points.size(); i++) {
      const Point p = points[i];
      if (p.type == -1) continue;

      const Point q = points[(i + 1) % points.size()];

      if (p.is_above()) {
        ingredients[p.type] += sgn;
      } else {
        ingredients[p.type] -= sgn;
      }

      const int fruit = ingredients[0];
      const int choco = ingredients[1];

      if (fruit == 0 && p.cross(q) != 0) {
        res = max(res, choco);
      }
    }
  }

  return res;
}

int main() {
  int n, m;
  while (cin >> n >> m) {
    vector<Point> points;
    for (int i = 0; i < n + m; i++) {
      double x, y;
      cin >> x >> y;
      points.emplace_back(x * 1e7, y * 1e7, i < n);
    }

    int ans = 0;

    for (int i = n; i < n + m; i++) {
      vector<Point> centered;
      for (int j = 0; j < n + m; j++) {
        if (i == j) continue;

        centered.emplace_back(points[j] - points[i]);
      }

      centered.emplace_back(1, 0, -1);
      centered.emplace_back(0, 1, -1);
      centered.emplace_back(-1, 0, -1);
      centered.emplace_back(0, -1, -1);

      sort(centered.begin(), centered.end());
      ans = max(ans, sweep(centered));
    }

    cout << ans << endl;
  }
}
