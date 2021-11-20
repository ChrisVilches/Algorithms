#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld EPS = 1e-12;

inline int sgn(int n) { return n < 0 ? -1 : n > 0; }

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
  inline ld length() { return p.dist(q); }
  Point to_vec() { return p.to(q); }
  bool same_direction(Segment s) {
    int sgn1 = sgn(to_vec() ^ q.to(s.p));
    int sgn2 = sgn(q.to(s.p) ^ s.to_vec());
    return sgn1 == 0 || sgn2 == 0 || sgn1 == sgn2;
  }

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

  inline bool intersect(Segment s) { return s.dist(center) + EPS < radius; }

  ld arc(Segment incoming_tan, Segment outgoing_tan) {
    Point a = center.to(incoming_tan.q);
    Point b = center.to(outgoing_tan.p);
    ld angle = acos(a * b / (a.magnitude() * b.magnitude()));
    if (tangents_reflex_angle(incoming_tan, outgoing_tan)) angle -= 2 * M_PI;
    return fabs(angle * radius);
  }

  bool arc_intersects(Circle c, Segment incoming_tan, Segment outgoing_tan) {
    if (center.dist(c.center) > radius + c.radius) return false;

    if (tangents_reflex_angle(incoming_tan, outgoing_tan)) {
      Segment tan = incoming_tan;
      bool intersect1 = sgn(tan.to_vec() ^ tan.q.to(center)) ==
                        sgn(center.to(c.center) ^ center.to(outgoing_tan.p));
      tan = outgoing_tan.invert();
      bool intersect2 = sgn(tan.to_vec() ^ tan.q.to(center)) ==
                        sgn(center.to(c.center) ^ center.to(incoming_tan.q));
      return intersect1 || intersect2;
    }

    Segment to_circle = Segment(center, c.center);
    return !incoming_tan.same_direction(to_circle) &&
           !outgoing_tan.invert().same_direction(to_circle);
  }

  array<Segment, 4> tangents_to(Circle c) {
    return array<Segment, 4>{external_tangents(c)[0], external_tangents(c)[1],
                             internal_tangents(c)[0], internal_tangents(c)[1]};
  }

  array<Segment, 2> tangents_from_point(Point p) {
    ld a = radius, b = p.dist(center);
    ld th = acos(a / b);
    ld d = atan2(p.y - center.y, p.x - center.x);
    ld d1 = d + th, d2 = d - th;
    return array<Segment, 2>{
        Segment(p, Point(center.x + a * cos(d1), center.y + a * sin(d1))),
        Segment(p, Point(center.x + a * cos(d2), center.y + a * sin(d2)))};
  }

 private:
  bool tangents_reflex_angle(Segment in, Segment out) {
    return in.same_direction(Segment(center, out.p));
  }

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
};

vector<Circle> poles;
Point robot(0, 0), goal;
ld min_dist;

bool movement_valid(Segment& s) {
  for (int i = 0; i < (int)poles.size(); i++)
    if (poles[i].intersect(s)) return false;
  return true;
}

bool tangent_movement_valid(int pole_idx, Segment& in_tan, Segment& out_tan) {
  if (!in_tan.same_direction(out_tan)) return false;
  for (int i = 0; i < (int)poles.size(); i++) {
    if (pole_idx == i) continue;
    if (poles[pole_idx].arc_intersects(poles[i], in_tan, out_tan)) return false;
  }
  return movement_valid(out_tan);
}

void traverse(int pole_idx, Segment& from, bitset<8> visited, ld dist) {
  if (dist > min_dist) return;
  Circle& curr_pole = poles[pole_idx];

  for (Segment& tangent : curr_pole.tangents_from_point(goal)) {
    tangent = tangent.invert();
    if (!tangent_movement_valid(pole_idx, from, tangent)) continue;
    min_dist =
        min(min_dist, dist + tangent.length() + curr_pole.arc(from, tangent));
    return;
  }

  for (int i = 0; i < (int)poles.size(); i++)
    if (!visited[i])
      for (Segment& tangent : curr_pole.tangents_to(poles[i]))
        if (tangent_movement_valid(pole_idx, from, tangent)) {
          ld arc = curr_pole.arc(from, tangent);
          bitset<8> v = visited;
          traverse(i, tangent, v.set(i), dist + tangent.length() + arc);
        }
}

void solve() {
  Segment direct_robot_goal(robot, goal);

  if (movement_valid(direct_robot_goal)) {
    printf("%.5Lf\n", direct_robot_goal.length());
    return;
  }

  for (int i = 0; i < (int)poles.size(); i++)
    for (Segment& tangent : poles[i].tangents_from_point(robot))
      if (movement_valid(tangent))
        traverse(i, tangent, bitset<8>(1 << i), tangent.length());

  printf("%.8Lf\n", min_dist == DBL_MAX ? 0.0 : min_dist);
}

int main() {
  int N;

  while (scanf("%d", &N) == 1) {
    min_dist = DBL_MAX;
    poles.clear();
    scanf("%Le %Le", &goal.x, &goal.y);

    while (N--) {
      Point p;
      scanf("%Le %Le", &p.x, &p.y);
      poles.push_back(Circle(p, 100L));
    }
    solve();
  }
}
