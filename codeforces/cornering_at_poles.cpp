#include <bits/stdc++.h>

using namespace std;
typedef long double ld;
#define PI 3.14159265358979323846

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

  ld dist_point(Point P) {
    Segment L = *this;
    if ((P - L.p) * L.to_vec() < 0)
      return P.dist(L.p);
    else if ((P - L.q) * L.to_vec() > 0)
      return P.dist(L.q);
    else
      return fabs(L.to_vec() ^ (P - L.p)) / L.to_vec().magnitude();
  }
};

struct Circle;
array<Segment, 2> point_circle_tangents(Point p, Circle c);

struct Circle {
  Point center;
  ld radius;
  Circle(Point c, ld r) : center(c), radius(r) {}

  inline bool intersect(Segment s) { return s.dist_point(center) < radius; }

  ld arc(Segment incoming_tan, Segment outgoing_tan) {
    Point a = center.to(incoming_tan.q);
    Point b = center.to(outgoing_tan.p);
    ld angle = acos(a * b / (a.magnitude() * b.magnitude()));
    if (tangents_reflex_angle(incoming_tan, outgoing_tan)) angle -= 2 * PI;
    return fabs(angle * radius);
  }

  bool arc_intersects(Circle c, Segment incoming_tan, Segment outgoing_tan) {
    if (center.dist(c.center) >= radius + c.radius) return false;
    Segment tan = incoming_tan;

    if (tangents_reflex_angle(incoming_tan, outgoing_tan)) {
      bool intersect1 = sgn(tan.to_vec() ^ tan.q.to(center)) ==
                        sgn(center.to(c.center) ^ center.to(outgoing_tan.p));
      tan = outgoing_tan.invert();
      bool intersect2 = sgn(tan.to_vec() ^ tan.q.to(center)) ==
                        sgn(center.to(c.center) ^ center.to(incoming_tan.q));
      return intersect1 || intersect2;
    } else {
      bool intersect1 = sgn(tan.to_vec() ^ tan.q.to(center)) !=
                        sgn(tan.q.to(center) ^ center.to(c.center));
      tan = outgoing_tan.invert();
      bool intersect2 = sgn(tan.to_vec() ^ tan.q.to(center)) !=
                        sgn(tan.q.to(center) ^ center.to(c.center));
      return intersect1 && intersect2;
    }
  }

  array<Segment, 4> tangents_to(Circle c) {
    return array<Segment, 4>{external_tangents(c)[0], external_tangents(c)[1],
                             internal_tangents(c)[0], internal_tangents(c)[1]};
  }

 private:
  bool tangents_reflex_angle(Segment in, Segment out) {
    return sgn(in.to_vec() ^ in.q.to(center)) ==
           sgn(in.q.to(center) ^ center.to(out.p));
  }

  array<Segment, 2> external_tangents(Circle c) {
    Point shift1 = center.to(c.center).normalize().rot_cw().scale(radius);
    Point shift2 = center.to(c.center).normalize().rot_ccw().scale(radius);
    return array<Segment, 2>{Segment(center + shift1, c.center + shift1),
                             Segment(center + shift2, c.center + shift2)};
  }

  array<Segment, 2> internal_tangents(Circle c) {
    Point mid = Segment(center, c.center).scale(0.5L).q;
    auto point_tans1 = point_circle_tangents(mid, c);
    auto point_tans2 = point_circle_tangents(mid, *this);
    return array<Segment, 2>{Segment(point_tans2[0].q, point_tans1[0].q),
                             Segment(point_tans2[1].q, point_tans1[1].q)};
  }
};

vector<Circle> poles;
Point robot(0, 0), goal;
ld min_dist;

array<Segment, 2> point_circle_tangents(Point p, Circle c) {
  ld a = c.radius, b = p.dist(c.center);
  ld th = acos(a / b);
  ld d = atan2(p.y - c.center.y, p.x - c.center.x);
  ld d1 = d + th, d2 = d - th;
  return array<Segment, 2>{
      Segment(p, Point(c.center.x + a * cos(d1), c.center.y + a * sin(d1))),
      Segment(p, Point(c.center.x + a * cos(d2), c.center.y + a * sin(d2)))};
}

bool movement_possible(Segment& s, int ignore_pole_idx1, int ignore_pole_idx2) {
  for (int i = 0; i < (int)poles.size(); i++) {
    if (i == ignore_pole_idx1 || i == ignore_pole_idx2) continue;
    if (poles[i].intersect(s)) return false;
  }
  return true;
}

bool valid_tangent_traversal(int pole_idx, Segment& in_tan, Segment& out_tan) {
  if (!in_tan.same_direction(out_tan)) return false;
  for (int i = 0; i < (int)poles.size(); i++) {
    if (pole_idx == i) continue;
    if (poles[pole_idx].arc_intersects(poles[i], in_tan, out_tan)) return false;
  }
  return true;
}

void traverse(int pole_idx, Segment& from, bitset<8> visited, ld dist) {
  if (dist > min_dist) return;
  Circle& curr_pole = poles[pole_idx];

  for (Segment& tangent : point_circle_tangents(goal, curr_pole)) {
    tangent = tangent.invert();
    if (!valid_tangent_traversal(pole_idx, from, tangent)) continue;
    if (!movement_possible(tangent, pole_idx, -1)) continue;
    min_dist =
        min(min_dist, dist + tangent.length() + curr_pole.arc(from, tangent));
    return;
  }

  for (int i = 0; i < (int)poles.size(); i++) {
    if (visited[i]) continue;

    for (Segment& tangent : curr_pole.tangents_to(poles[i])) {
      if (!valid_tangent_traversal(pole_idx, from, tangent)) continue;
      if (!movement_possible(tangent, pole_idx, i)) continue;

      ld arc = curr_pole.arc(from, tangent);
      bitset<8> v = visited;
      traverse(i, tangent, v.set(i), dist + tangent.length() + arc);
    }
  }
}

void solve() {
  Segment direct_robot_goal(robot, goal);

  if (movement_possible(direct_robot_goal, -1, -1)) {
    printf("%.5Lf\n", direct_robot_goal.length());
    return;
  }

  for (int i = 0; i < (int)poles.size(); i++)
    for (Segment& tangent : point_circle_tangents(robot, poles[i]))
      if (movement_possible(tangent, i, -1)) {
        bitset<8> visited;
        traverse(i, tangent, visited.set(i), tangent.length());
      }

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
