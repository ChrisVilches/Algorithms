#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point rot_ccw() const { return {-y, x}; }
  bool operator<(const Point p) const { return x < p.x || (x == p.x && y < p.y); }
};

ll area_rect(const Point p, const Point q) { return abs(p.x - q.x) * abs(p.y - q.y); }

ll remove_area(vector<Point>& points) {
  sort(points.begin(), points.end());

  ll min_y = LONG_LONG_MAX;
  for (const Point p : points) min_y = min(min_y, p.y);

  vector<Point> new_fence_points;

  ll area_removed = 0;

  Point last = points.front();

  for (const Point p : points) {
    if (p.y < last.y) {
      new_fence_points.push_back({p.x - 1, last.y - 1});
      area_removed += area_rect({p.x, min_y}, last);
      last = p;
    }
  }

  copy(new_fence_points.begin(), new_fence_points.end(), back_inserter(points));

  return area_removed;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N) {
    vector<Point> points(N);
    for (Point& p : points) cin >> p.x >> p.y;

    ll min_x = LONG_LONG_MAX, min_y = LONG_LONG_MAX;
    ll max_x = LONG_LONG_MIN, max_y = LONG_LONG_MIN;

    for (const Point p : points) {
      min_x = min(min_x, p.x);
      max_x = max(max_x, p.x);
      min_y = min(min_y, p.y);
      max_y = max(max_y, p.y);
    }

    const ll x_side = max_x - min_x + 2;
    const ll y_side = max_y - min_y + 2;

    const ll perimeter = 2LL * (x_side + y_side);
    ll area = x_side * y_side;

    for (int rot = 0; rot < 4; rot++) {
      area -= remove_area(points);
      for (Point& p : points) p = p.rot_ccw();
    }

    cout << perimeter << " " << area << endl;
  }
}
