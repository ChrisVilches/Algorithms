#include <bits/stdc++.h>

using namespace std;
typedef long double ld;

inline bool error_equal(ld a, ld b) { return fabs(a - b) < 1e-8; }

inline int sgn(int n) {
  if (n == 0) return 0;
  if (n > 0) return 1;
  return -1;
}

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

  string str() {
    stringstream ss;
    ss << "(" << x << ", " << y << ")";
    return ss.str();
  }
};

struct Segment {
  Point p, q;
  Segment(Point p, Point q) : p(p), q(q) {}
  Segment() {}
  Segment invert() { return Segment(q, p); }
  inline ld length() { return p.dist(q); }

  bool same_direction(Segment s) {
    int sgn1 = sgn(p.to(q) ^ q.to(s.p));
    int sgn2 = sgn(q.to(s.p) ^ s.p.to(s.q));
    return sgn1 == sgn2;
  }

  string str() {
    stringstream ss;
    ss << p.str() << " -> " << q.str();
    return ss.str();
  }
};

struct Circle;
Segment point_circle_tangent1(Point p, Circle c);
Segment point_circle_tangent2(Point p, Circle c);

struct Circle {
  Point center;
  ld radius;
  Circle(Point c, ld r) : center(c), radius(r) {}
  bool intersect(Segment s) {
    ld left = 0L;
    ld right = 1L;
    int iters = 500;
    Point dir = s.p.to(s.q);
    while (iters--) {
      ld third = (right - left) / 3L;
      ld third1 = left + third;
      ld third2 = right - third;
      Point p1 = s.p + dir.scale(third1);
      Point p2 = s.p + dir.scale(third2);
      if (p1.dist(center) > p2.dist(center)) {
        left = third1;
      } else {
        right = third2;
      }
      assert(left >= 0 && left <= 1L);
      assert(right >= 0 && right <= 1L);
    }

    Point closest_point = (s.p + dir.scale(left));

    assert(error_equal(left, right));

    if (point_in_circumference(closest_point)) return true;

    return closest_point.dist(center) < radius;
  }

  bool point_in_circumference(Point p) {
    return error_equal(p.dist(center), radius);
  }

  ld arc(Segment incoming_tan, Segment outgoing_tan) {
    // assert(is_incoming_tangent(incoming_tan));
    // assert(is_outgoing_tangent(outgoing_tan));
    // assert(incoming_tan.same_direction(outgoing_tan));

    Point incoming_vec = incoming_tan.p.to(incoming_tan.q);
    Point incoming_to_center = incoming_tan.q.to(center);
    Point center_to_out_vec = center.to(outgoing_tan.p);

    Point center_in = center.to(incoming_tan.q);
    Point center_out = center.to(outgoing_tan.p);

    bool more_than_180 = sgn(incoming_vec ^ incoming_to_center) ==
                         sgn(incoming_to_center ^ center_to_out_vec);

    ld angle = acos(center_in * center_out /
                    (center_in.magnitude() * center_out.magnitude()));

    if (more_than_180) angle = 2 * M_PI - angle;

    return fabs(angle * radius);
  }

  bool circle_intersects_arc(Circle c, Segment incoming_tan,
                             Segment outgoing_tan) {
    // assert(is_incoming_tangent(incoming_tan));
    // assert(is_outgoing_tangent(outgoing_tan));
    // assert(incoming_tan.same_direction(outgoing_tan));

    Segment tan = incoming_tan;

    bool close_enough = center.dist(c.center) < radius + c.radius;

    if (!close_enough) return false;

    bool intersect1 = sgn(tan.p.to(tan.q) ^ tan.q.to(center)) !=
                      sgn(tan.q.to(center) ^ center.to(c.center));

    tan = outgoing_tan.invert();

    bool intersect2 = sgn(tan.p.to(tan.q) ^ tan.q.to(center)) !=
                      sgn(tan.q.to(center) ^ center.to(c.center));

    // if (error_equal(tan.p.to(tan.q) ^ tan.q.to(center), 0) &&
    //    error_equal((tan.q.to(center) ^ center.to(c.center)), 0))
    //  return true;

    return intersect1 && intersect2;
  }

  bool is_incoming_tangent(Segment s) {
    return point_in_circumference(s.q) &&
           error_equal(s.p.to(s.q) * s.q.to(center), 0);
  }

  bool is_outgoing_tangent(Segment s) {
    return is_incoming_tangent(s.invert());
  }

  Segment circle_circle_external_tangent1(Circle c) {
    Point shift = center.to(c.center).normalize().rotate1().scale(radius);
    return Segment(center + shift, c.center + shift);
  }

  Segment circle_circle_external_tangent2(Circle c) {
    Point shift = center.to(c.center).normalize().rotate2().scale(radius);
    return Segment(center + shift, c.center + shift);
  }
  // TODO: External tangent not implemented correctly yet
  // It's probably correct but maybe I got the same tangent, so I need to check.
  Segment circle_circle_internal_tangent1(Circle c) {
    Point mid = center + center.to(c.center).scale(0.5L);
    Point q = point_circle_tangent1(mid, c).q;
    Point p = point_circle_tangent1(mid, Circle(center, radius)).q;
    assert(point_in_circumference(p));
    assert(c.point_in_circumference(q));
    return Segment(p, q);
  }
  // TODO: External tangent not implemented correctly yet
  Segment circle_circle_internal_tangent2(Circle c) {
    Point mid = center + center.to(c.center).scale(0.5L);
    Point q = point_circle_tangent2(mid, c).q;
    Point p = point_circle_tangent2(mid, Circle(center, radius)).q;
    assert(point_in_circumference(p));
    assert(c.point_in_circumference(q));
    return Segment(p, q);
  }
};

vector<Circle> poles;
Point goal;
Point robot(0, 0);
ld min_dist;

Segment point_circle_tangent1(Point p, Circle c) {
  ld a = c.radius;
  ld b = p.dist(c.center);
  ld th = acos(a / b);
  ld d = atan2(p.y - c.center.y, p.x - c.center.x);
  ld d1 = d + th;
  return Segment(p, Point(c.center.x + a * cos(d1), c.center.y + a * sin(d1)));
}

Segment point_circle_tangent2(Point p, Circle c) {
  ld a = c.radius;
  ld b = p.dist(c.center);
  assert(a <= b);
  ld th = acos(a / b);
  ld d = atan2(p.y - c.center.y, p.x - c.center.x);
  ld d2 = d - th;
  return Segment(p, Point(c.center.x + a * cos(d2), c.center.y + a * sin(d2)));
}

bool valid_segment(Segment& s, int ignore_pole_idx1, int ignore_pole_idx2) {
  for (int i = 0; i < (int)poles.size(); i++) {
    if (i == ignore_pole_idx1) continue;
    if (i == ignore_pole_idx2) continue;
    if (poles[i].intersect(s)) {
      // cerr << "Segment" << s.str() << " intersects with pole_idx=" << i << "
      // "
      //    << poles[i].center.str() << endl;
      return false;
    }
  }
  return true;
}

bool valid_tangent_traversal(int pole_idx, Segment in_tan, Segment out_tan) {
  // if (!in_tan.same_direction(out_tan)) return false; // Kind of doesn't work
  // for some reason Maybe for collinear vectors it doesn't work properly.
  for (int i = 0; i < (int)poles.size(); i++) {
    if (pole_idx == i) continue;
    if (poles[pole_idx].circle_intersects_arc(poles[i], in_tan, out_tan))
      return false;
  }

  return true;
}

void traverse(int pole_idx, Segment from, bitset<8> visited, ld dist,
              int depth) {
  string spaces;
  for (int i = 0; i < depth; i++) {
    spaces += "  ";
  }
  // cerr << spaces << "Arrived to " << poles[pole_idx].center.str()
  //     << " on point " << from.q.str() << endl;
  if (dist > min_dist) return;
  assert(poles[pole_idx].is_incoming_tangent(from));

  Segment to_goal_tangents[] = {
      point_circle_tangent1(goal, poles[pole_idx]).invert(),
      point_circle_tangent2(goal, poles[pole_idx]).invert()};

  bool found = false;

  for (int i = 0; i < 2; i++) {
    assert(poles[pole_idx].point_in_circumference(to_goal_tangents[i].p));
    assert(to_goal_tangents[i].q == goal);

    Segment& tangent = to_goal_tangents[i];
    //  cerr << spaces << "Direct path to goal is valid? "
    //       << valid_segment(tangent, pole_idx, -1)
    //      << ", is it a valid tangential movement? "
    //      << valid_tangent_traversal(pole_idx, from, tangent) << endl;
    // cerr << "Same direction? " << from.same_direction(tangent) << endl;
    bool valid = valid_tangent_traversal(pole_idx, from, tangent);
    valid = valid && valid_segment(tangent, pole_idx, -1);

    if (valid) {
      found = true;
      // cerr << spaces << "✅ From pole_idx " << pole_idx << " "
      //  << poles[pole_idx].center.str()
      // << " there is a direct path to goal"
      ////      << endl;
      // cerr << spaces << "The tangent to goal is " << tangent.str() <<
      // endl;
      ld arc = poles[pole_idx].arc(from, tangent);
      assert(arc >= 0);
      // fprintf(stderr, "Accum dist %Lf, arc length %Lf, final tangent %Lf\n",
      //        dist, arc, tangent.length());
      ld total_dist = dist + tangent.length() + arc;
      // cerr << spaces << "Updating dist: " << total_dist << endl;
      min_dist = min(min_dist, total_dist);
    }
  }

  // if (!found)  // return;
  //{
  ////  cerr << spaces << "There's no direct path from " << from.q.str()
  //       << " to goal " << goal.str() << endl;
  //}

  for (int i = 0; i < (int)poles.size(); i++) {
    if (visited[i]) continue;
    visited.set(i, true);

    vector<Segment> tangents{
        poles[pole_idx].circle_circle_external_tangent1(poles[i]),
        poles[pole_idx].circle_circle_external_tangent2(poles[i])};

    if (poles[pole_idx].center.dist(poles[i].center) >=
        poles[pole_idx].radius + poles[i].radius) {
      tangents.push_back(
          poles[pole_idx].circle_circle_internal_tangent1(poles[i]));
      tangents.push_back(
          poles[pole_idx].circle_circle_internal_tangent2(poles[i]));
    }

    for (Segment& tangent : tangents) {
      bool valid = valid_segment(tangent, pole_idx, i);
      valid = valid && valid_tangent_traversal(pole_idx, from, tangent);
      if (valid) {
        //   cerr << spaces << "Move to " << poles[i].center.str() << endl;
        ld arc = poles[pole_idx].arc(from, tangent);
        assert(arc >= 0);
        traverse(i, tangent, visited, dist + tangent.length() + arc, depth + 1);
      }
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

    Segment tangent1 = point_circle_tangent1(robot, poles[i]);
    Segment tangent2 = point_circle_tangent2(robot, poles[i]);

    // cerr << "Pole centered at: " << poles[i].center.str() << endl;
    // cerr << "Tangent is: " << tangent1.str() << endl;

    assert(poles[i].is_incoming_tangent(tangent1));
    assert(poles[i].is_incoming_tangent(tangent2));

    if (valid_segment(tangent1, i, -1)) {
      // cerr << "From main, it CAN travel (using tang1) to "
      //      << poles[i].center.str() << " pole_idx: " << i << endl;
      traverse(i, tangent1, visited, tangent1.length(), 1);

    } else {
      //  cerr << "From main, it cannot travel to pole_idx " << i << " "
      //       << poles[i].center.str() << " using tangent 1" << endl;
    }

    if (valid_segment(tangent2, i, -1)) {
      //  cerr << "From main, it CAN travel (using tang2) to "
      //       << poles[i].center.str() << " pole_idx: " << i << endl;
      traverse(i, tangent2, visited, tangent2.length(), 1);
    } else {
      //  cerr << "From main, it cannot travel to pole_idx " << i << " "
      //       << poles[i].center.str() << " using tangent 2" << endl;
    }
  }

  if (min_dist == DBL_MAX) {
    cout << "0.0" << endl;
  } else {
    printf("%.5Lf\n", min_dist);
  }
}

int main() {
  /*
  Circle c(Point(0, 0), 100);
  Circle c2 = Circle(Point(0, 1000), 100);

  assert(error_equal(c.arc(Segment(Point(-100, -100), Point(-100, 0)),
                           Segment(Point(0, 100), Point(100, 100))),
                     c.radius * M_PI / 2L));

  assert(error_equal(c.arc(Segment(Point(-100, -100), Point(-100, 0)),
                           Segment(Point(100, 0), Point(100, -100))),
                     c.radius * M_PI));

  assert(error_equal(c.arc(Segment(Point(-100, -100), Point(-100, 0)),
                           Segment(Point(0, -100), Point(-100, -100))),
                     c.radius * 3L * M_PI / 2L));

  assert(Circle(Point(0, 0), 100)
             .is_incoming_tangent(Segment(Point(-100, -100), Point(-100,
  0))));

  Segment tang = c.circle_circle_external_tangent1(c2);
  assert(c2.is_incoming_tangent(tang));
*/
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
