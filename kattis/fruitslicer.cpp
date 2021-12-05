#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld EPS = 1e-12;

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
  Point rot_ccw() { return Point(-y, x); }
  Point rot_cw() { return Point(y, -x); }
  Point normalize() { return Point(x / magnitude(), y / magnitude()); }
  Point scale(ld f) { return Point(x * f, y * f); }
};

struct Segment {
  Point p, q;
  Segment(Point p, Point q) : p(p), q(q) {}
  Segment() {}
  Segment invert() { return Segment(q, p); }
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

  inline bool intersect(Segment s) { return s.dist(center) < radius + EPS; }

  array<Segment, 2> external_tangents(Circle c) {
    Point shift1 = center.to(c.center).normalize().rot_cw().scale(radius);
    Point shift2 = center.to(c.center).normalize().rot_ccw().scale(radius);
    return array<Segment, 2>{Segment(center + shift1, c.center + shift1),
                             Segment(center + shift2, c.center + shift2)};
  }

  array<Segment, 2> internal_tangents(Circle c) {
    Point mid = Segment(center, c.center).scale(0.5L).q;
    auto point_tans1 = c.tangents_from_point(mid);
    auto point_tans2 = tangents_from_point(mid);
    return array<Segment, 2>{Segment(point_tans2[0].q, point_tans1[0].q),
                             Segment(point_tans2[1].q, point_tans1[1].q)};
  }

 private:
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

void solve() {
  vector<Circle> circles;

  for (int i = 0; i < N; i++) {
    Point p;
    scanf("%Le %Le", &p.x, &p.y);
    circles.push_back(Circle(p, 1L));
  }

  vector<Segment> all_segments;

  for (Circle c1 : circles)
    for (Circle c2 : circles) {
      // Hack to generate external tangents even if
      // the circle centers are the same.
      if (c1.center == c2.center) c1.center.x += EPS;

      array<Segment, 2> ext_tan = c1.external_tangents(c2);

      all_segments.push_back(ext_tan[0]);
      all_segments.push_back(ext_tan[1]);

      if (c1.center.dist(c2.center) < 2L) continue;

      array<Segment, 2> int_tan = c1.internal_tangents(c2);

      all_segments.push_back(int_tan[0]);
      all_segments.push_back(int_tan[1]);
    }

  // Make the line "infinite".
  for (Segment& s : all_segments) s = s.scale(20000L).invert().scale(20000L);

  int ans = 0;

  for (Segment& s : all_segments) {
    int count = 0;
    for (Circle& c : circles)
      if (c.intersect(s)) count++;

    ans = max(ans, count);
  }

  printf("%d\n", ans);
}

int main() {
  while (scanf("%d", &N) == 1) solve();
}
