#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
  ll x, y;
  ll original_x = 0;
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  bool operator<(const Point p) const { return x < p.x || (x == p.x && y < p.y); }
};

unordered_map<ll, ll> compute_lower_hull(vector<Point> points) {
  sort(points.begin(), points.end());
  unordered_map<ll, ll> res;

  vector<Point> hull(points.size());
  int k = 0;
  ll area = 0;

  for (const Point p : points) {
    if (res.count(p.original_x)) continue;

    while (k >= 2 && (hull[k - 1] - p).cross(hull[k - 2] - p) > 0) {
      area -= hull[k - 2].cross(hull[k - 1]);
      k--;
    }

    if (k > 0) area += hull[k - 1].cross(p);
    hull[k++] = p;
    res[p.original_x] = area;
  }

  return res;
}

int main() {
  int n;
  while (cin >> n) {
    vector<Point> points(n);
    for (Point& p : points) {
      cin >> p.x >> p.y;
      p.original_x = p.x;
    }

    unordered_map<ll, ll> lo_y, hi_y;

    for (const Point p : points) {
      lo_y[p.x] = INT_MAX;
      hi_y[p.x] = INT_MIN;
    }

    for (const Point p : points) {
      lo_y[p.x] = min(lo_y[p.x], p.y);
      hi_y[p.x] = max(hi_y[p.x], p.y);
    }

    const auto prefix_lower = compute_lower_hull(points);
    for (Point& p : points) p.y = -p.y;
    const auto prefix_upper = compute_lower_hull(points);
    for (Point& p : points) {
      p.x = -p.x;
      p.y = -p.y;
    }
    const auto suffix_lower = compute_lower_hull(points);
    for (Point& p : points) p.y = -p.y;
    const auto suffix_upper = compute_lower_hull(points);

    unordered_map<ll, ll> vertical_edges;
    vector<ll> xs;

    for (const auto& [x, _] : lo_y) {
      xs.emplace_back(x);
      vertical_edges[x] = Point{x, lo_y[x]}.cross({x, hi_y[x]});
    }

    sort(xs.begin(), xs.end());

    ll ans = LLONG_MAX;

    const ll left = -vertical_edges[xs.front()];
    const ll right = vertical_edges[xs.back()];

    for (size_t i = 0; i < xs.size(); i++) {
      ll total = 0;

      if (i > 0) {
        const ll x = xs[i - 1];
        total += left + prefix_lower.at(x) + prefix_upper.at(x) + vertical_edges[x];
      }

      const ll x = xs[i];
      total += right + suffix_lower.at(x) + suffix_upper.at(x) - vertical_edges[x];

      ans = min(ans, total);
    }

    cout << (ans + (ans % 2)) / 2 << endl;
  }
}
