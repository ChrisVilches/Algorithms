#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

enum PointType { RED = 0, BLUE = 1 };

struct Point {
  ll x, y;
  PointType type;

  Point move_to_upper() const {
    if (y > 0) return {x, y, type};
    if (y < 0) return {-x, -y, type};
    if (x > 0) return {x, y, type};
    return {-x, y, type};
  }

  Point operator-(const Point& p) const { return {x - p.x, y - p.y, type}; }
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

int calculate_loss(const vector<Point>& points, const PointType above_type) {
  const PointType below_type = above_type == BLUE ? RED : BLUE;

  array<int, 2> destroyed = {0, 0};

  for (const Point& p : points) {
    if (p.is_above() && p.type == below_type) destroyed[p.type]++;
    if (!p.is_above() && p.type == above_type) destroyed[p.type]++;
  }

  int ans = destroyed[0] + destroyed[1];

  for (const Point& p : points) {
    if (p.is_above())
      destroyed[p.type] += p.type == above_type ? 1 : -1;
    else
      destroyed[p.type] += p.type == below_type ? 1 : -1;

    ans = min(ans, destroyed[0] + destroyed[1]);
  }

  return ans;
}

void solve() {
  int N, M;
  cin >> N >> M;
  vector<Point> points(N + M);

  for (int i = 0; i < N + M; i++) {
    cin >> points[i].x >> points[i].y;
    points[i].type = i < N ? RED : BLUE;
  }

  int ans = INT_MAX;

  for (const Point& center : points) {
    vector<Point> centered_points;
    for (const Point& p : points) {
      if (p == center) continue;
      centered_points.push_back(p - center);
    }

    sort(centered_points.begin(), centered_points.end(), cmp);

    const int loss_red = calculate_loss(centered_points, RED);
    const int loss_blue = calculate_loss(centered_points, BLUE);
    ans = min({ans, loss_red, loss_blue});
  }

  cout << ans << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
