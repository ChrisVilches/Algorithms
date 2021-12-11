#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
  Point() {}

  Point move_to_upper() const {
    if (y > 0) return Point(x, y);
    if (y < 0) return Point(-x, -y);
    if (x > 0) return Point(x, y);
    return Point(-x, y);
  }

  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  int operator^(const Point& p) const { return x * p.y - y * p.x; }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
};

bool cmp(const Point& p, const Point& q) {
  return (p.move_to_upper() ^ q.move_to_upper()) > 0;
}

int N;

int count(vector<Point>& points) {
  if (points.empty()) return 1;
  int ans = 2;
  int curr = 2;

  for (int i = 0; i < (int)points.size(); i++) {
    Point p = points[i];
    Point next_point = points[(i + 1) % points.size()];

    ans = max(ans, curr);

    if ((p ^ next_point) == 0)
      curr++;
    else
      curr = 2;
  }
  return ans;
}

void solve() {
  vector<Point> points;

  for (int i = 0; i < N; i++) {
    Point p;
    scanf("%d %d", &p.x, &p.y);
    points.push_back(p);
  }

  int ans = 1;

  for (const Point& center : points) {
    vector<Point> centered_points;
    for (const Point& p : points) {
      if (p == center) continue;
      centered_points.push_back(p - center);
    }

    sort(centered_points.begin(), centered_points.end(), cmp);
    ans = max(ans, count(centered_points));
  }

  printf("%d\n", ans);
}

int main() {
  while (scanf("%d", &N) == 1 && N > 0) solve();
}
