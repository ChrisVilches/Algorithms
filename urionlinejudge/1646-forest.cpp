#include <bits/stdc++.h>
typedef long double ld;
const ld EPS = 1e-8;
using namespace std;

struct Point {
  ld x, y;
  Point(ld x, ld y) : x(x), y(y) {}
  Point() {}

  Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  inline ld operator^(const Point& p) const { return (x * p.y) - (y * p.x); }
  inline ld operator*(const Point& p) const { return (x * p.x) + (y * p.y); }
  inline bool operator==(const Point& p) const { return x == p.x && y == p.y; }
  Point to(const Point& p) const { return p - *this; }
  inline ld magnitude() { return sqrt((x * x) + (y * y)); }
  inline ld dist(const Point& p) { return to(p).magnitude(); }
  Point scale(ld f) { return Point(x * f, y * f); }
};

struct Segment {
  Point p, q;
  Segment(Point p, Point q) : p(p), q(q) {}
  Segment() {}
  Segment scale(ld f) { return Segment(p, p + p.to(q).scale(f)); }
  Point to_vec() { return p.to(q); }
  ld dist(Point P) {
    Segment L = *this;
    if ((P - L.p) * L.to_vec() < 0)
      return P.dist(L.p);
    else if ((P - L.q) * L.to_vec() > 0)
      return P.dist(L.q);
    else
      return fabs(L.to_vec() ^ (P - L.p)) / L.to_vec().magnitude();
  }
};

struct Circle {
  Point center;
  ld radius;
  Circle(Point c, ld r) : center(c), radius(r) {}

  inline bool intersect(Segment s) { return s.dist(center) <= radius; }

  array<Segment, 2> tangents_from_point(Point p) {
    ld a = radius, b = p.dist(center);
    ld th = acos(a / b);
    ld d = atan2(p.y - center.y, p.x - center.x);
    ld d1 = d + th, d2 = d - th;
    return array<Segment, 2>{
        Segment(p, Point(center.x + a * cos(d1), center.y + a * sin(d1))),
        Segment(p, Point(center.x + a * cos(d2), center.y + a * sin(d2)))};
  }
};

int N;
vector<Circle> trees;

inline ld dist_closest_point(Circle& c) {
  return c.center.magnitude() - c.radius;
}

ld distance_to_first_visible_circle(Segment s) {
  ld left = 0;
  ld right = 1L;

  s = s.scale(1e4 * sqrt(2) * 2.3L);
  ld min_dist = 0;

  while (fabs(left - right) > 0.00001L) {
    ld mid = (left + right) / 2L;
    bool intersects = false;

    for (int i = 0; i < (int)trees.size(); i++)
      if (trees[i].intersect(s.scale(mid))) {
        min_dist = dist_closest_point(trees[i]);
        intersects = true;
        break;
      }

    if (intersects)
      right = mid;
    else
      left = mid;
  }

  return min_dist;
}

void solve() {
  trees.clear();

  for (int i = 0; i < N; i++) {
    Point p;
    ld r;
    cin >> p.x >> p.y >> r;
    trees.push_back(Circle(p, r));
  }

  ld ans = 0;

  sort(trees.begin(), trees.end(), [](Circle& c1, Circle& c2) {
    return dist_closest_point(c1) < dist_closest_point(c2);
  });

  vector<Segment> segments;

  for (Circle c : trees) {
    c.radius += EPS;
    array<Segment, 2> tangents = c.tangents_from_point(Point(0, 0));
    segments.push_back(tangents[0]);
    segments.push_back(tangents[1]);
    segments.push_back(Segment(Point(0, 0), c.center));
  }

  for (Segment& s : segments)
    ans = max(ans, distance_to_first_visible_circle(s));

  printf("%.3Lf\n", ans);
}

int main() {
  while (scanf("%d", &N) == 1 && N > 0) solve();
}
