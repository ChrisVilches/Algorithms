#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  Point rotate() const { return {-y, x}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  bool operator<(const Point& p) const { return x < p.x || (x == p.x && y < p.y); }
};

void solve() {
  int N;
  cin >> N;

  vector<Point> points(N);
  for (auto& p : points) cin >> p.x >> p.y;
  set<Point> present{points.begin(), points.end()};

  int ans = 0;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      const Point vec = (points[j] - points[i]).rotate();
      const Point p1 = points[i] + vec;
      const Point p2 = points[j] + vec;

      ans += (present.count(p1) && present.count(p2));
    }
  }

  cout << ans / 4 << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
