#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
  ll x, y;

  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
  bool operator<(const Point p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
};

ll c2(const int n) { return (n * (n - 1)) / 2; }

ll count(const vector<Point>& points) {
  const int n = points.size();
  ll sum = 0;

  for (int i = 0, j = 1; i < n; i++) {
    while (j < i || points[i].cross(points[(j + 1) % n]) > 0) j++;

    const ll side1 = c2(j - i);
    const ll side2 = c2(n - (j - i) - 1);

    sum += side1 * side2;
  }

  return sum;
}

int main() {
  int n;
  while (cin >> n) {
    ll ans = 0;

    vector<Point> points(n);
    for (Point& p : points) cin >> p.x >> p.y;

    for (int i = 0; i < n; i++) {
      vector<Point> centered_points;

      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        centered_points.push_back(points[j] - points[i]);
      }

      sort(centered_points.begin(), centered_points.end());

      ans += count(centered_points);
    }

    cout << ans / 2LL << endl;
  }
}
