#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  double cross(const Point p) const { return x * p.y - y * p.x; }
  double dist(const Point p) const { return hypot(p.x - x, p.y - y); }
};

int orientation(const Point o, const Point p, const Point q) {
  const double x = (p - o).cross(q - o);
  return (x > 0) - (x < 0);
}

int main() {
  int n;
  while (cin >> n) {
    Point start{0, 0}, goal{0, static_cast<double>(n)};
    cin >> start.x >> goal.x;
    vector<pair<Point, Point>> walls(n + 1);

    for (int i = 0; i <= n; i++) {
      cin >> walls[i].first.x >> walls[i].second.x;
      walls[i].first.y = i;
      walls[i].second.y = i;
    }

    walls.back() = {goal, goal};

    Point l, r, p = start;
    tie(l, r) = walls.front();

    double ans = 0;

    for (int i = 0; i <= n; i++) {
      const auto [new_l, new_r] = walls[i];

      if (orientation(p, l, new_l) <= 0) l = new_l;
      if (orientation(p, r, new_r) >= 0) r = new_r;

      if (orientation(p, l, new_r) == 1) {
        ans += p.dist(l);
        p = l;
        i = p.y;
        tie(l, r) = walls[i + 1];
      }

      if (orientation(p, r, new_l) == -1) {
        ans += p.dist(r);
        p = r;
        i = p.y;
        tie(l, r) = walls[i + 1];
      }
    }

    ans += p.dist(goal);

    cout << fixed << setprecision(12) << ans << endl;
  }
}
