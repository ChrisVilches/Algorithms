#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int P, L;

// WIP. Accepted on URI.
// Wrong answer on UVa. One case failing (test data from uDebug)

enum PointType { PINE = 0, LARCH = 1 };

struct Point {
  ll x, y;
  PointType type;
  int value;
  Point(ll x, ll y, PointType type, int v) : x(x), y(y), type(type), value(v) {}
  Point() {}
  Point move_to_upper() {
    if (y > 0) return Point(x, y, type, value);
    return Point(-x, -y, type, value);
  }

  Point move_to_upper_zero_means_above() {
    if (y >= 0) return Point(x, y, type, value);
    return Point(-x, -y, type, value);
  }

  Point operator-(const Point& p) const {
    return Point(x - p.x, y - p.y, type, value);
  }
  inline ll operator^(const Point& p) const { return x * p.y - y * p.x; }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
  bool operator<(const Point& p) const { return (*this ^ p) > 0; }

  bool is_above(bool zero_means_above) const {
    if (zero_means_above) {
      return y >= 0;
    } else {
      return y > 0;
    }
  }
};

ll cross(const Point& p1, const Point& p2) {
  return (p1.x * p2.y) - (p1.y * p2.x);
}

bool cmp_zero_means_above(Point p, Point q) {
  Point p2 = p.move_to_upper_zero_means_above();
  Point q2 = q.move_to_upper_zero_means_above();
  return (p2 ^ q2) > 0;
}

bool cmp(Point p, Point q) {
  Point p2 = p.move_to_upper();
  Point q2 = q.move_to_upper();
  return (p2 ^ q2) > 0;
}

int calculate_loss(vector<Point>& points, PointType above_type,
                   bool zero_means_above) {
  PointType below_type = above_type == LARCH ? PINE : LARCH;

  array<int, 2> destroyed = {0, 0};

  for (const Point& p : points) {
    if (p.is_above(zero_means_above) && p.type == below_type)
      destroyed[p.type] += p.value;

    if (!p.is_above(zero_means_above) && p.type == above_type)
      destroyed[p.type] += p.value;
  }

  int ans = destroyed[0] + destroyed[1];

  for (int i = 0; i < (int)points.size(); i++) {
    const Point& p = points[i];

    if (p.is_above(zero_means_above)) {
      destroyed[p.type] += p.type == above_type ? p.value : -p.value;
    } else {
      destroyed[p.type] += p.type == below_type ? p.value : -p.value;
    }

    bool next_collinear = false;

    if (i < (int)points.size() - 1) {
      Point next_point = points[i + 1];
      next_collinear = (p ^ next_point) == 0;
    }

    if (!next_collinear) {
      ans = min(ans, destroyed[0] + destroyed[1]);
    }
  }

  return ans;
}

void solve() {
  vector<Point> points;

  for (int i = 0; i < P; i++) {
    Point p;
    scanf("%lld %lld %d", &p.x, &p.y, &p.value);
    p.type = PINE;
    points.push_back(p);
  }

  for (int i = 0; i < L; i++) {
    Point p;
    scanf("%lld %lld %d", &p.x, &p.y, &p.value);
    p.type = LARCH;
    points.push_back(p);
  }

  int ans = INT_MAX;

  for (Point& center : points) {
    vector<Point> centered_points;
    for (Point& p : points) {
      if (p == center) continue;
      centered_points.push_back(p - center);
    }

    int loss_pine, loss_larch;

    sort(centered_points.begin(), centered_points.end(), cmp_zero_means_above);
    loss_pine = calculate_loss(centered_points, PINE, true);
    loss_larch = calculate_loss(centered_points, LARCH, true);
    ans = min({ans, loss_pine, loss_larch});

    sort(centered_points.begin(), centered_points.end(), cmp);
    loss_pine = calculate_loss(centered_points, PINE, false);
    loss_larch = calculate_loss(centered_points, LARCH, false);
    ans = min({ans, loss_pine, loss_larch});
  }

  cout << ans << endl;
}

int main() {
  while (scanf("%d %d", &P, &L) && P && L) solve();
}
