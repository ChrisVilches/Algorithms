#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

struct Point {
  ld x, y;
  Point(ld x, ld y) : x(x), y(y) {}
  Point() {}
  Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  Point rot_ccw() { return Point(-y, x); }
  Point normalize() { return Point(x / magnitude(), y / magnitude()); }
  Point scale(ld f) { return Point(x * f, y * f); }
  ld cross(const Point& p) const { return x * p.y - y * p.x; }
  Point negate() { return Point(-x, -y); }
  bool operator<(const Point& p) const { return cross(p) > 0; }
  ld magnitude() const { return sqrt(x * x + y * y); }
  inline bool is_first_quad() { return x >= 0 && y >= 0; }
};

array<Point, 2> points_of_tangency(ld radius, const Point& from_point) {
  ld a = radius, b = from_point.magnitude();
  ld th = acos(a / b);
  ld d = atan2(from_point.y, from_point.x);
  ld d1 = d + th, d2 = d - th;
  Point p1 = Point(a * cos(d1), a * sin(d1));
  Point p2 = Point(a * cos(d2), a * sin(d2));
  return array<Point, 2>{p1, p2};
}

vector<Point> points;

bool possible(ld side) {
  ld half_side = side / 2L;
  ld half_diagonal = half_side * sqrt(2);

  vector<pair<Point, bool>> events;

  int inside = 0;

  for (Point& p : points) {
    if (p.magnitude() < half_side) return false;
    if (p.magnitude() > half_diagonal) continue;

    // Points of tangency from p to the inscribed circle inside the square.
    auto [t1, t2] = points_of_tangency(half_side, p);

    // Vectors that reach a square vertex when added to the points of tangency.
    Point u = (p - t1).normalize().scale(half_side);
    Point v = (p - t2).normalize().scale(half_side);

    // Radial sweep is [0, 90] degrees, so find the ones in the first quadrant.
    Point event1 = (t1 + u).is_first_quad() ? (t1 + u) : (t1 + u.negate());
    Point event2 = (t2 + v).is_first_quad() ? (t2 + v) : (t2 + v.negate());

    if (event2 < event1) swap(event1, event2);

    bool point_initially_inside = p.y < half_diagonal - p.x;

    // When it starts inside the square, it will exit and then enter again.
    // When it starts outside the square, it will enter and then exit.
    if (point_initially_inside) {
      inside++;
      events.push_back(make_pair(event1, false));
      events.push_back(make_pair(event2, true));
    } else {
      events.push_back(make_pair(event1, true));
      events.push_back(make_pair(event2, false));
    }
  }

  if (events.empty()) return true;

  sort(events.begin(), events.end(),
       [](const pair<Point, bool>& a, const pair<Point, bool>& b) {
         return a.first < b.first;
       });

  // It's possible to build the square if there's at least one rotation with no
  // points inside.
  // Radial sweep of square diagonal, from 0 to 90 degrees.
  for (pair<Point, bool> ev : events) {
    auto [_, enter] = ev;
    inside += enter ? 1 : -1;
    if (inside == 0) return true;
  }

  return false;
}

int main() {
  int N;

  while (scanf("%d", &N) == 1) {
    points.clear();

    while (N--) {
      Point p;
      cin >> p.x >> p.y;
      points.push_back(p);
    }

    for (Point& p : points)
      while (!p.is_first_quad()) p = p.rot_ccw();

    ld left = 0;
    ld right = 1e9 * sqrt(2) * 100;

    while (right - left > 0.00001L) {
      ld mid = (left + right) / 2L;
      if (possible(mid))
        left = mid;
      else
        right = mid;
    }

    printf("%.4Lf\n", 4 * left);
  }
}
