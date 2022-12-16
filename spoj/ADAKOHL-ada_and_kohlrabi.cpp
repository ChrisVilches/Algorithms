#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  int x, y, value;
  Point move_to_upper() const { return is_above() ? *this : Point{-x, -y, value}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y, value}; }
  ll cross(const Point& p) const { return (ll)x * p.y - (ll)y * p.x; }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
};

bool cmp(const Point& p, const Point& q) {
  return p.move_to_upper().cross(q.move_to_upper()) > 0;
}

int calculate(const vector<Point>& points) {
  int res = 0;
  int curr_line = 0;

  for (int i = 0; i < (int)points.size(); i++) {
    const Point p = points[i];
    const Point q = points[(i + 1) % points.size()];

    curr_line += p.value;

    if (p.cross(q) != 0 || i == (int)points.size() - 1) {
      res = max(res, curr_line);
      curr_line = 0;
    }
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T, N;
  cin >> T;

  while (T--) {
    cin >> N;
    vector<Point> points(N);

    for (Point& p : points) cin >> p.x >> p.y >> p.value;

    int ans = 0;

    for (const Point& center : points) {
      vector<Point> centered_points;
      for (const Point& p : points) {
        if (p == center) continue;
        centered_points.push_back(p - center);
      }

      sort(centered_points.begin(), centered_points.end(), cmp);
      ans = max(ans, center.value + calculate(centered_points));
    }

    cout << ans << '\n';
  }
}
