#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  ll cross(const Point& p) const { return x * p.y - y * p.x; }
  bool operator<(const Point p) const { return x < p.x || (x == p.x && y < p.y); }
};

struct Rectangle {
  ll x1, y1, x2, y2;

  Rectangle rot_ccw() const { return {-y1, x1, -y2, x2}; }

  array<Point, 4> points() const {
    const auto [min_x, max_x] = minmax(x1, x2);
    const auto [min_y, max_y] = minmax(y1, y2);
    return {Point{min_x, min_y}, {max_x, min_y}, {max_x, max_y}, {min_x, max_y}};
  }
};

vector<Rectangle> rectangles;

short orientation(const Point& o, const Point& a, const Point& b) {
  const ll cross = (a - o).cross(b - o);
  return cross < 0 ? -1 : cross > 0;
}

vector<Point> create_lower_hull(vector<Point> points) {
  if (points.size() < 2) return points;

  sort(points.begin(), points.end());

  int k = 0;

  for (const Point p : points) {
    while (k > 1 && orientation(points[k - 2], points[k - 1], p) <= 0) k--;
    points[k++] = p;
  }

  points.resize(k);

  return points;
}

bool all_points_direction(const vector<Point>& edges, const vector<Point>& points,
                          const bool above) {
  const short dir = above ? -1 : 1;

  for (int i = 0, j = 0; i < (int)edges.size() - 1; i++) {
    const Point p = edges[i];
    const Point q = edges[i + 1];

    while (j < (int)points.size() && points[j].x < p.x) j++;

    while (j < (int)points.size() && points[j].x <= q.x) {
      if (orientation(p, q, points[j]) == dir) return false;

      j++;
    }
  }

  return true;
}

bool intersection(vector<Point> upper, vector<Point> lower) {
  upper = create_lower_hull(upper);
  for (Point& p : lower) p.y *= -1;
  lower = create_lower_hull(lower);
  for (Point& p : lower) p.y *= -1;

  return !all_points_direction(lower, upper, true) ||
         !all_points_direction(upper, lower, false);
}

bool possible() {
  for (int rot = 0; rot < 2; rot++) {
    vector<Point> top_left, top_right, bottom_left, bottom_right;

    for (const Rectangle r : rectangles) {
      const array<Point, 4> points = r.points();
      bottom_left.push_back(points[0]);
      bottom_right.push_back(points[1]);
      top_right.push_back(points[2]);
      top_left.push_back(points[3]);
    }

    if (!intersection(top_left, bottom_right) || !intersection(top_right, bottom_left)) {
      return true;
    }

    for (Rectangle& r : rectangles) r = r.rot_ccw();
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N) {
    rectangles.resize(N);
    for (Rectangle& rect : rectangles) {
      cin >> rect.x1 >> rect.y1;
      cin >> rect.x2 >> rect.y2;
    }

    cout << (possible() ? "possible" : "impossible") << endl;
  }
}
