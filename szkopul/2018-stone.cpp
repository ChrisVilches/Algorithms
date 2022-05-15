#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }

  ll cross(const Point& p) const { return x * p.y - y * p.x; }

  bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }

  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
  inline ll dist2() const { return x * x + y * y; }
};

int N;

ll calculate(const vector<Point>& points) {
  Point curr{0, 0};
  ll ans = 0;

  for (int i = 0, j = 0; i < (int)points.size(); i++) {
    curr = curr + points[i];

    while (j < i) {
      const ll new_dist = (curr - points[j]).dist2();

      if (new_dist > curr.dist2()) {
        curr = curr - points[j];
        j++;
      } else {
        break;
      }
    }

    ans = max(ans, curr.dist2());
  }

  return ans;
}

void solve() {
  vector<Point> points;

  for (int i = 0; i < N; i++) {
    ll x, y;
    cin >> x >> y;
    if (x == 0 && y == 0) continue;

    points.push_back({x, y});
  }

  ll a, b, c, d;

  sort(points.begin(), points.end());
  a = calculate(points);

  reverse(points.begin(), points.end());
  b = calculate(points);

  for (Point& p : points) p.x *= -1;

  sort(points.begin(), points.end());
  c = calculate(points);

  reverse(points.begin(), points.end());
  d = calculate(points);

  cout << max({a, b, c, d}) << endl;
}

int main() {
  while (cin >> N) solve();
}
