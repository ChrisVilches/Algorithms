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
  // TODO: Rename rotate1/2 and tangent1/2, use something more meaningful.
  Point rotate1() { return Point(y, -x); }
  Point rotate2() { return Point(-y, x); }
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

  bool operator==(const Segment& s) const { return p == s.p && q == s.q; }
  bool same_direction(Segment s) {
    int sgn1 = sgn(p.to(q) ^ q.to(s.p));
    int sgn2 = sgn(q.to(s.p) ^ s.p.to(s.q));
    if ((sgn1 == 0) ^ (sgn2 == 0)) return true;
    return sgn1 == sgn2;
  }
};

struct Circle;
array<Segment, 2> point_circle_tangents(Point p, Circle c);

// TODO: Make this class universal (not just related to "poles"). Or at least as
// universal as possible.
struct Circle {
  Point center;
  ld radius;
  Circle(Point c, ld r) : center(c), radius(r) {}

  bool intersect(Segment s) {
    ld left = 0L, right = 1L;
    while (fabs(left - right) > 0.001L) {
      ld third = (right - left) / 3L;
      ld third1 = left + third, third2 = right - third;
      if (s.scale(third1).q.dist(center) > s.scale(third2).q.dist(center))
        left = third1;
      else
        right = third2;
    }
    return s.scale(left).q.dist(center) < radius;
  }

  // TODO: Simplify!!
  ld arc(Segment incoming_tan, Segment outgoing_tan) {
    Point incoming_vec = incoming_tan.p.to(incoming_tan.q);
    Point incoming_to_center = incoming_tan.q.to(center);
    Point center_to_out_vec = center.to(outgoing_tan.p);

    Point center_in = center.to(incoming_tan.q);
    Point center_out = center.to(outgoing_tan.p);

    bool more_than_180 = sgn(incoming_vec ^ incoming_to_center) ==
                         sgn(incoming_to_center ^ center_to_out_vec);

    ld angle = acos(center_in * center_out /
                    (center_in.magnitude() * center_out.magnitude()));

    if (more_than_180) angle -= 2 * PI;

    return fabs(angle * radius);
  }

  // TODO: Wow lol simplify
  bool circle_intersects_arc(Circle c, Segment incoming_tan,
                             Segment outgoing_tan) {
    Segment tan = incoming_tan;
    bool close_enough = center.dist(c.center) < radius + c.radius;
    if (!close_enough) return false;
    if ((center.to(tan.q) ^ center.to(c.center)) == 0) return false;
    int a = sgn(tan.p.to(tan.q) ^ tan.q.to(center));
    int b = sgn(tan.q.to(center) ^ center.to(c.center));
    bool intersect1 = a != b && (b != 0);
    tan = outgoing_tan.invert();
    if ((center.to(tan.q) ^ center.to(c.center)) == 0) return false;
    a = sgn(tan.p.to(tan.q) ^ tan.q.to(center));
    b = sgn(tan.q.to(center) ^ center.to(c.center));
    bool intersect2 = a != b && (b != 0);
    int in_direction =
        sgn(incoming_tan.p.to(incoming_tan.q) ^ incoming_tan.q.to(center));
    int out = sgn(incoming_tan.q.to(center) ^ center.to(outgoing_tan.p));
    if (in_direction == out) {
      if (sgn(incoming_tan.q.to(center) ^ center.to(c.center)) != out)
        return true;
      int xx = incoming_tan.p.to(incoming_tan.q) ^ incoming_tan.q.to(center);
      int yy = center.to(c.center) ^ center.to(outgoing_tan.p);
      if (sgn(xx) == sgn(yy)) return true;
    }
    return intersect1 && intersect2;
  }

  array<Segment, 4> tangents_to(Circle c) {
    // TODO: Simplify
    array<Segment, 4> ret;
    ret[0] = circle_circle_external_tangents(c)[0];
    ret[1] = circle_circle_external_tangents(c)[1];
    ret[2] = circle_circle_internal_tangents(c)[0];
    ret[3] = circle_circle_internal_tangents(c)[1];
    return ret;
  }

 private:
  array<Segment, 2> circle_circle_external_tangents(Circle c) {
    Point shift1 = center.to(c.center).normalize().rotate1().scale(radius);
    Point shift2 = center.to(c.center).normalize().rotate2().scale(radius);
    return array<Segment, 2>{Segment(center + shift1, c.center + shift1),
                             Segment(center + shift2, c.center + shift2)};
  }

  array<Segment, 2> circle_circle_internal_tangents(Circle c) {
    Point mid = center + center.to(c.center).scale(0.5L);
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
  ld a = c.radius;
  ld b = p.dist(c.center);
  ld th = acos(a / b);
  ld d = atan2(p.y - c.center.y, p.x - c.center.x);
  ld d1 = d + th, d2 = d - th;
  return array<Segment, 2>{
      Segment(p, Point(c.center.x + a * cos(d1), c.center.y + a * sin(d1))),
      Segment(p, Point(c.center.x + a * cos(d2), c.center.y + a * sin(d2)))};
}

// TODO: Rename so that the 2nd and 3rd arguments make more sense.
bool valid_segment(Segment& s, int ignore_pole_idx1, int ignore_pole_idx2) {
  for (int i = 0; i < (int)poles.size(); i++) {
    if (i == ignore_pole_idx1 || i == ignore_pole_idx2) continue;
    if (poles[i].intersect(s)) return false;
  }
  return true;
}

bool valid_tangent_traversal(int pole_idx, Segment in_tan, Segment out_tan) {
  if (!in_tan.same_direction(out_tan)) return false;
  for (int i = 0; i < (int)poles.size(); i++) {
    if (pole_idx == i) continue;
    if (poles[pole_idx].circle_intersects_arc(poles[i], in_tan, out_tan))
      return false;
  }

  return true;
}

void traverse(int pole_idx, Segment from, bitset<8> visited, ld dist) {
  if (dist > min_dist) return;
  Circle curr_pole = poles[pole_idx];

  for (Segment& tangent : point_circle_tangents(goal, curr_pole)) {
    tangent = tangent.invert();
    if (!valid_tangent_traversal(pole_idx, from, tangent)) continue;
    if (!valid_segment(tangent, pole_idx, -1)) continue;

    ld arc = curr_pole.arc(from, tangent);
    ld total_dist = dist + tangent.length() + arc;
    min_dist = min(min_dist, total_dist);
    return;
  }

  for (int i = 0; i < (int)poles.size(); i++) {
    if (visited[i]) continue;

    for (Segment& tangent : curr_pole.tangents_to(poles[i])) {
      if (!valid_tangent_traversal(pole_idx, from, tangent)) continue;
      if (!valid_segment(tangent, pole_idx, i)) continue;

      ld arc = curr_pole.arc(from, tangent);
      bitset<8> next_visited = visited;
      next_visited.set(i, true);
      traverse(i, tangent, next_visited, dist + tangent.length() + arc);
    }
  }
}

void solve() {
  min_dist = DBL_MAX;

  Segment direct_robot_goal(robot, goal);

  if (valid_segment(direct_robot_goal, -1, -1)) {
    printf("%.5Lf\n", direct_robot_goal.length());
    return;
  }

  for (int i = 0; i < (int)poles.size(); i++) {
    bitset<8> visited;
    visited.set(i, true);

    for (Segment& tangent : point_circle_tangents(robot, poles[i]))
      if (valid_segment(tangent, i, -1))
        traverse(i, tangent, visited, tangent.length());
  }

  printf("%.13Lf\n", min_dist == DBL_MAX ? 0.0 : min_dist);
}

int main() {
  int N;

  while (scanf("%d", &N) == 1) {
    poles.clear();
    cin >> goal.x >> goal.y;

    while (N--) {
      Point p;
      cin >> p.x >> p.y;
      poles.push_back(Circle(p, 100L));
    }
    solve();
  }
}
