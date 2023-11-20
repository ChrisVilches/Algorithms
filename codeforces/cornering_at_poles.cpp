#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-12;

/*
 * Gets AC, but there's one case where it doesn't work.
 * If a pole has to be visited twice in order to get to the goal, then it fails.
 * The Dijkstra version works OK.
 * The failing case is here:
 * https://github.com/ChrisVilches/Algorithms/issues/30
 * */

inline int sgn(int n) { return n < 0 ? -1 : n > 0; }

struct Point {
  double x, y;
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline double operator^(const Point& p) const { return (x * p.y) - (y * p.x); }
  inline double operator*(const Point& p) const { return (x * p.x) + (y * p.y); }
  Point to(const Point& p) const { return p - *this; }
  inline double magnitude() const { return hypot(x, y); }
  inline double dist(const Point& p) const { return to(p).magnitude(); }
  Point rot_ccw() const { return {-y, x}; }
  Point rot_cw() const { return {y, -x}; }
  Point normalize() const { return {x / magnitude(), y / magnitude()}; }
  Point scale(double f) const { return {x * f, y * f}; }
};

struct Segment {
  Point p, q;
  Segment invert() { return {q, p}; }
  Segment scale(double f) { return {p, p + p.to(q).scale(f)}; }
  inline double length() { return p.dist(q); }
  Point to_vec() { return p.to(q); }
  double dist(Point r) {
    if ((q - p) * (r - p) <= 0) return p.dist(r);
    if ((p - q) * (r - q) <= 0) return q.dist(r);
    return fabs((q - p) ^ (r - p)) / p.dist(q);
  }
};

// NOTE: Internal tangents will have NaN coordinates if the circles intersect.
//       But in this program it's not necessary to manually handle these cases.
struct Circle {
  Point center;
  const double radius = 100;

  inline bool intersect(Segment s) { return s.dist(center) + EPS < radius; }

  double arc(Segment incoming_tan, Segment outgoing_tan) {
    Point a = center.to(incoming_tan.q);
    Point b = center.to(outgoing_tan.p);
    double angle = acos(a * b / (a.magnitude() * b.magnitude()));
    if (tangents_reflex_angle(incoming_tan, outgoing_tan)) angle -= 2 * M_PI;
    return fabs(angle * radius);
  }

  bool tangents_same_direction(Segment in_tan, Segment out_tan) {
    return same_direction(in_tan.p, in_tan.q, out_tan.p, out_tan.q);
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

    return !same_direction(incoming_tan.p, incoming_tan.q, center, c.center) &&
           !same_direction(outgoing_tan.q, outgoing_tan.p, center, c.center);
  }

  array<Segment, 4> tangents_to(Circle c) {
    return array<Segment, 4>{external_tangents(c)[0], external_tangents(c)[1],
                             internal_tangents(c)[0], internal_tangents(c)[1]};
  }

  array<Segment, 2> tangents_from_point(Point p) {
    double a = radius, b = p.dist(center);
    double th = acos(a / b);
    double d = atan2(p.y - center.y, p.x - center.x);
    double d1 = d + th, d2 = d - th;
    return array<Segment, 2>{Segment{p, {center.x + a * cos(d1), center.y + a * sin(d1)}},
                             {p, {center.x + a * cos(d2), center.y + a * sin(d2)}}};
  }

 private:
  bool tangents_reflex_angle(Segment in, Segment out) {
    return same_direction(in.p, in.q, center, out.p);
  }

  array<Segment, 2> external_tangents(Circle c) {
    Point shift1 = center.to(c.center).normalize().rot_cw().scale(radius);
    Point shift2 = center.to(c.center).normalize().rot_ccw().scale(radius);
    return array<Segment, 2>{Segment{center + shift1, c.center + shift1},
                             {center + shift2, c.center + shift2}};
  }

  array<Segment, 2> internal_tangents(Circle c) {
    Point mid = Segment{center, c.center}.scale(0.5).q;
    auto point_tans1 = c.tangents_from_point(mid);
    auto point_tans2 = tangents_from_point(mid);
    return array<Segment, 2>{Segment{point_tans2[0].q, point_tans1[0].q},
                             {point_tans2[1].q, point_tans1[1].q}};
  }

  bool same_direction(Point a, Point b, Point c, Point d) {
    int sgn1 = sgn(a.to(b) ^ b.to(c));
    int sgn2 = sgn(b.to(c) ^ c.to(d));
    return sgn1 == 0 || sgn2 == 0 || sgn1 == sgn2;
  }
};

vector<Circle> poles;
Point robot{0, 0}, goal;
double min_dist;

bool movement_valid(Segment& s) {
  for (Circle p : poles)
    if (p.intersect(s)) return false;
  return true;
}

bool tangent_movement_valid(int pole_idx, Segment& in_tan, Segment& out_tan) {
  if (!poles[pole_idx].tangents_same_direction(in_tan, out_tan)) return false;
  for (int i = 0; i < (int)poles.size(); i++) {
    if (pole_idx == i) continue;
    if (poles[pole_idx].arc_intersects(poles[i], in_tan, out_tan)) return false;
  }
  return movement_valid(out_tan);
}

void traverse(int pole_idx, Segment& from, bitset<8> visited, double dist) {
  if (dist > min_dist) return;
  Circle& curr_pole = poles[pole_idx];

  for (Segment& tangent : curr_pole.tangents_from_point(goal)) {
    tangent = tangent.invert();
    if (!tangent_movement_valid(pole_idx, from, tangent)) continue;
    min_dist = min(min_dist, dist + tangent.length() + curr_pole.arc(from, tangent));
    return;
  }

  for (int i = 0; i < (int)poles.size(); i++)
    if (!visited[i])
      for (Segment& tangent : curr_pole.tangents_to(poles[i]))
        if (tangent_movement_valid(pole_idx, from, tangent)) {
          double arc = curr_pole.arc(from, tangent);
          bitset<8> v = visited;
          traverse(i, tangent, v.set(i), dist + tangent.length() + arc);
        }
}

void solve() {
  Segment direct_robot_goal{robot, goal};

  if (movement_valid(direct_robot_goal)) {
    min_dist = direct_robot_goal.length();
    return;
  }

  for (int i = 0; i < (int)poles.size(); i++)
    for (Segment& tangent : poles[i].tangents_from_point(robot))
      if (movement_valid(tangent))
        traverse(i, tangent, bitset<8>(1 << i), tangent.length());
}

int main() {
  int N;

  while (cin >> N >> goal.x >> goal.y) {
    min_dist = DBL_MAX;
    poles.resize(N);
    for (auto& p : poles) cin >> p.center.x >> p.center.y;
    solve();
    cout << fixed << setprecision(9) << (min_dist == DBL_MAX ? 0.0 : min_dist) << endl;
  }
}
