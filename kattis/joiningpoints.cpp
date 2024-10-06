#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  Point rot_ccw() const { return {-y, x}; }
};

bool inside(const int x, const int a, const int b) {
  return min(a, b) <= x && x <= max(a, b);
}

bool valid(const vector<Point>& points, const Point p, const Point q) {
  for (const auto& [x, y] : points) {
    const bool ok1 = (y == p.y || y == q.y) && inside(x, p.x, q.x);
    const bool ok2 = (x == p.x || x == q.x) && inside(y, p.y, q.y);
    if (!ok1 && !ok2) return false;
  }

  return true;
}

optional<pair<Point, Point>> solve(vector<Point> points) {
  for (int r = 0; r < 4; r++) {
    int min_x = 1e9;
    int min_y = 1e9;
    int max_y = -1e9;
    for (const auto& p : points) {
      min_x = min(min_x, p.x);
      min_y = min(min_y, p.y);
      max_y = max(max_y, p.y);
    }
    const int side = max_y - min_y;
    const int max_x = min_x + side;
    Point p{min_x, min_y};
    Point q{max_x, max_y};

    if (valid(points, p, q)) {
      for (int i = 0; i < 4 - r; i++) {
        p = p.rot_ccw();
        q = q.rot_ccw();
      }

      return pair<Point, Point>{p, q};
    }

    for (auto& p : points) p = p.rot_ccw();
  }

  return nullopt;
}

int main() {
  int n;
  cin >> n;
  vector<Point> points(n);
  for (auto& [x, y] : points) cin >> x >> y;

  const auto sol = solve(points);

  if (sol.has_value()) {
    const auto [p, q] = sol.value();
    const auto [x1, x2] = minmax(p.x, q.x);
    const auto [y1, y2] = minmax(p.y, q.y);
    cout << x1 << ' ' << x2 << ' ' << y1 << ' ' << y2 << endl;
  } else {
    cout << "Impossible" << endl;
  }
}
