#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
  ll x, y;
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  bool first_half() const { return y > 0 || (y == 0 && x > 0); }
  bool operator<(const Point p) const {
    return first_half() != p.first_half() ? first_half() : cross(p) > 0;
  }
  ll operator*(const Point p) const { return x * p.x + y * p.y; }
};

void compute(const vector<Point>& points, ll& obtuse, ll& right) {
  const int n = points.size();

  for (int i = 0, j = 1, k = 1; i < n; i++) {
    const Point p = points[i];

    if (p.cross(points[(i + 1) % n]) < 0) continue;

    while (k < i || p.cross(points[(k + 1) % n]) > 0) k++;

    const ll window_dot = p * points[k % n];

    if (window_dot >= 0) {
      right += window_dot == 0;
      continue;
    }

    if (j <= i) j = i + 1;

    while (j < k) {
      const ll dot = p * points[j % n];

      if (dot == 0) {
        right++;
        obtuse--;
      }

      if (dot <= 0) break;

      j++;
    }

    obtuse += k - j + 1;
  }
}

int main() {
  ll n;

  while (cin >> n) {
    vector<Point> points(n);
    for (Point& p : points) cin >> p.x >> p.y;

    ll obtuse = 0;
    ll right = 0;

    for (int i = 0; i < n; i++) {
      vector<Point> centered;
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        centered.emplace_back(points[j] - points[i]);
      }
      sort(centered.begin(), centered.end());
      compute(centered, obtuse, right);
    }

    const ll all = n * (n - 1) * (n - 2) / 6;
    const ll acute = all - right - obtuse;

    cout << format("{} {} {}", acute, right, obtuse) << endl;
  }
}
