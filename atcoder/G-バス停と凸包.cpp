#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = 1e9 + 7;

struct Point {
  ll x, y;
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  bool first_half() const { return y > 0 || (y == 0 && x > 0); }
  bool operator<(const Point p) const {
    return first_half() != p.first_half() ? first_half() : cross(p) > 0;
  }
};

vector<ll> pow2{1};

int main() {
  for (int i = 1; i <= 2000; i++) {
    pow2.emplace_back(pow2[i - 1] * 2);
    pow2.back() %= mod;
  }

  int n;
  while (cin >> n) {
    vector<Point> points(n);
    for (Point& p : points) cin >> p.x >> p.y;
    ll ans = 0;

    for (int c = 0; c < n; c++) {
      const Point center = points[c];
      vector<Point> centered;
      for (int i = 0; i < n; i++) {
        if (c == i) continue;
        centered.emplace_back(points[i] - center);
      }

      sort(centered.begin(), centered.end());

      for (int i = 0, j = 0; i < n - 1; i++) {
        const Point p = centered[i];

        if (j < i) j = i;
        while (p.cross(centered[(j + 1) % (n - 1)]) > 0) j++;

        ans += pow2[j - i] * center.cross(center + p);
        ans = (ans + mod) % mod;
      }
    }

    cout << ans << endl;
  }
}
