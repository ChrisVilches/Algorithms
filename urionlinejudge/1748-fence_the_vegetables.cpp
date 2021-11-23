#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point(ll x, ll y) : x(x), y(y) {}
  Point() {}
  void rotate() {
    y = -y;
    swap(x, y);
  }

  bool operator<(const Point& p) const {
    if (x == p.x) return y < p.y;
    return x < p.x;
  }
};

int V;

ll area_rect(const Point& p, const Point& q) {
  return abs(p.x - q.x) * abs(p.y - q.y);
}

ll remove_area(vector<Point>& points) {
  sort(points.begin(), points.end());

  ll min_y = LONG_LONG_MAX;
  for (Point& p : points) min_y = min(min_y, p.y);

  vector<Point> new_fence_points;

  ll area_removed = 0;

  Point last = points[0];

  for (const Point& p : points)
    if (p.y < last.y) {
      new_fence_points.push_back(Point(p.x - 1, last.y - 1));
      area_removed += area_rect(Point(p.x, min_y), Point(last.x, last.y));
      last = p;
    }

  for (Point& p : new_fence_points) points.push_back(p);

  return area_removed;
}

void remove_and_rotate(vector<Point>& points, ll* area) {
  ll area_removed = remove_area(points);
  *area -= area_removed;
  for (Point& p : points) p.rotate();
}

void solve() {
  vector<Point> points;

  for (int i = 0; i < V; i++) {
    Point p;
    cin >> p.x >> p.y;
    points.push_back(p);
  }

  ll min_x = LONG_LONG_MAX, min_y = LONG_LONG_MAX;
  ll max_x = LONG_LONG_MIN, max_y = LONG_LONG_MIN;

  for (Point& p : points) {
    min_x = min(min_x, p.x);
    max_x = max(max_x, p.x);
    min_y = min(min_y, p.y);
    max_y = max(max_y, p.y);
  }

  ll x_side = max_x - min_x + 2;
  ll y_side = max_y - min_y + 2;

  ll perimeter = 2 * (x_side + y_side);
  ll area = x_side * y_side;

  for (int i = 0; i < 4; i++) remove_and_rotate(points, &area);

  cout << perimeter << " " << area << endl;
}

int main() {
  while (scanf("%d", &V) == 1) solve();
}
