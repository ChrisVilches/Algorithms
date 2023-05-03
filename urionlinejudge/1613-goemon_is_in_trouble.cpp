#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  int cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  bool operator<(const Point p) const { return cross(p) > 0; }
};

void solve() {
  int P, G;

  Point center;
  cin >> center.x >> center.y;

  cin >> P;

  vector<pair<Point, Point>> walls;
  vector<Point> goemon;

  for (int i = 0; i < P; i++) {
    int s, e;
    cin >> s >> e;
    walls.emplace_back(Point{0, s} - center, Point{0, e} - center);
  }

  cin >> G;

  for (int i = 0; i < G; i++) {
    Point p;
    cin >> p.x >> p.y;
    goemon.emplace_back(p - center);
  }

  sort(walls.begin(), walls.end());
  sort(goemon.begin(), goemon.end());

  int ans = 0;

  auto it = goemon.begin();

  for (const auto& [start, end] : walls) {
    while (it != goemon.end() && it->cross(end) > 0) {
      if (start.cross(*it) > 0) ans++;
      it++;
    }
  }

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;
  while (T--) solve();
}
