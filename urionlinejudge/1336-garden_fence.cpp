#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int P, L;

enum PointType { PINE = 0, LARCH = 1 };

struct Point {
  ll x, y;
  PointType type;
  int value;

  Point move_to_upper() const {
    if (y > 0) return {x, y, type, value};
    if (y < 0) return {-x, -y, type, value};
    if (x > 0) return {x, y, type, value};
    return {-x, y, type, value};
  }

  Point operator-(const Point& p) const { return {x - p.x, y - p.y, type, value}; }
  ll operator^(const Point& p) const { return x * p.y - y * p.x; }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }

  bool is_above() const {
    if (y != 0) return y > 0;
    return x > 0;
  }
};

bool cmp(const Point& p, const Point& q) {
  return (p.move_to_upper() ^ q.move_to_upper()) > 0;
}

int calculate_loss(vector<Point>& points, PointType above_type) {
  PointType below_type = above_type == LARCH ? PINE : LARCH;

  array<int, 2> destroyed = {0, 0};

  for (const Point& p : points) {
    if (p.is_above() && p.type == below_type) destroyed[p.type] += p.value;
    if (!p.is_above() && p.type == above_type) destroyed[p.type] += p.value;
  }

  int ans = destroyed[0] + destroyed[1];

  for (int i = 0; i < (int)points.size(); i++) {
    const Point& p = points[i];

    if (p.is_above())
      destroyed[p.type] += p.type == above_type ? p.value : -p.value;
    else
      destroyed[p.type] += p.type == below_type ? p.value : -p.value;

    Point next_point = points[(i + 1) % points.size()];
    bool next_collinear = (p ^ next_point) == 0;

    if (!next_collinear) ans = min(ans, destroyed[0] + destroyed[1]);
  }

  return ans;
}

void solve() {
  vector<Point> points;

  for (int i = 0; i < P + L; i++) {
    Point p;
    scanf("%lld %lld %d", &p.x, &p.y, &p.value);
    p.type = i < P ? PINE : LARCH;
    points.push_back(p);
  }

  int ans = INT_MAX;

  for (const Point& center : points) {
    vector<Point> centered_points;
    for (const Point& p : points) {
      if (p == center) continue;
      centered_points.push_back(p - center);
    }

    sort(centered_points.begin(), centered_points.end(), cmp);

    int loss_pine = calculate_loss(centered_points, PINE);
    int loss_larch = calculate_loss(centered_points, LARCH);
    ans = min({ans, loss_pine, loss_larch});
  }

  printf("%d\n", ans);
}

int main() {
  while (scanf("%d %d", &P, &L) && P && L) solve();
}
