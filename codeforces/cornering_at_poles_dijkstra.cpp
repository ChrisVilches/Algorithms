#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef pair<ld, int> pdi;
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

// NOTE: Internal tangents will have NaN coordinates if the circles intersect.
//       But in this program it's not necessary to manually handle these cases.
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
    return same_direction(in.p, in.q, center, out.p);
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

  bool same_direction(Point a, Point b, Point c, Point d) {
    int sgn1 = sgn(a.to(b) ^ b.to(c));
    int sgn2 = sgn(b.to(c) ^ c.to(d));
    return sgn1 == 0 || sgn2 == 0 || sgn1 == sgn2;
  }
};

struct Node {
  Point point;
  int id;
  vector<pdi> edges;
  Node(Point p, int id) : point(p), id(id) {}
  Node() {}
};

vector<Circle> poles;
Point robot(0, 0), goal;
ld min_dist;

bool movement_valid(Segment& s) {
  for (int i = 0; i < (int)poles.size(); i++)
    if (poles[i].intersect(s)) return false;
  return true;
}

bool arc_intersect_any_circle(int pole_idx, Segment& in_tan, Segment& out_tan) {
  for (int i = 0; i < (int)poles.size(); i++) {
    if (pole_idx == i) continue;
    if (poles[pole_idx].arc_intersects(poles[i], in_tan, out_tan)) return true;
  }
  return false;
}

vector<Node> graph;
unordered_map<int, vector<int>> points_in_pole;
int node_id;

int add_node(Point p, int pole_idx) {
  int new_node_id = node_id;
  graph.push_back(Node(p, node_id++));
  if (pole_idx > -1) points_in_pole[pole_idx].push_back(new_node_id);
  return new_node_id;
}

inline int add_node(Point p) { return add_node(p, -1); }

void solve() {
  node_id = 0;
  graph.clear();
  Segment direct_robot_goal(robot, goal);

  if (movement_valid(direct_robot_goal)) {
    printf("%.5Lf\n", direct_robot_goal.length());
    return;
  }

  for (int i = 0; i < (int)poles.size(); i++) points_in_pole[i] = vector<int>();

  const int ROBOT_NODE_ID = add_node(robot);
  const int GOAL_NODE_ID = add_node(goal);

  for (int i = 0; i < (int)poles.size(); i++) {
    for (Segment& tangent : poles[i].tangents_from_point(robot))
      if (movement_valid(tangent)) {
        int n = add_node(tangent.q, i);
        graph[ROBOT_NODE_ID].edges.push_back({tangent.length(), n});
      }

    for (Segment& tangent : poles[i].tangents_from_point(goal))
      if (movement_valid(tangent)) {
        int n = add_node(tangent.q, i);
        graph[n].edges.push_back({tangent.length(), GOAL_NODE_ID});
      }

    for (int j = i + 1; j < (int)poles.size(); j++)
      for (Segment& tangent : poles[i].tangents_to(poles[j]))
        if (movement_valid(tangent)) {
          int n1 = add_node(tangent.p, i);
          int n2 = add_node(tangent.q, j);
          graph[n1].edges.push_back({tangent.length(), n2});
          graph[n2].edges.push_back({tangent.length(), n1});
        }
  }

  for (int i = 0; i < (int)poles.size(); i++) {
    for (int j = 0; j < (int)points_in_pole[i].size(); j++)
      for (int k = j + 1; k < (int)points_in_pole[i].size(); k++) {
        int p1 = points_in_pole[i][j];
        int p2 = points_in_pole[i][k];

        Point center = poles[i].center;
        Point in_pt = graph[p1].point;
        Point out_pt = graph[p2].point;

        array<pair<Segment, Segment>, 4> tangent_combinations{
            make_pair(Segment(in_pt + center.to(in_pt).rot_ccw(), in_pt),
                      Segment(out_pt, out_pt + center.to(out_pt).rot_cw())),
            make_pair(Segment(in_pt + center.to(in_pt).rot_cw(), in_pt),
                      Segment(out_pt, out_pt + center.to(out_pt).rot_ccw()))};

        for (pair<Segment, Segment> combination : tangent_combinations) {
          auto [in_tan, out_tan] = combination;
          if (!arc_intersect_any_circle(i, in_tan, out_tan)) {
            ld arc = poles[i].arc(in_tan, out_tan);
            graph[p1].edges.push_back({arc, p2});
            graph[p2].edges.push_back({arc, p1});
          }
        }
      }
  }

  vector<ld> dist(graph.size(), DBL_MAX);

  priority_queue<pdi, vector<pdi>, greater<pdi>> q;

  q.push({0, ROBOT_NODE_ID});
  dist[ROBOT_NODE_ID] = 0;

  while (!q.empty()) {
    auto [_, u] = q.top();
    q.pop();
    for (auto& [weight, v] : graph[u].edges) {
      ld alt = dist[u] + weight;
      if (alt < dist[v]) {
        dist[v] = alt;
        q.push({alt, v});
      }
    }
  }

  printf("%.8Lf\n", dist[GOAL_NODE_ID] == DBL_MAX ? 0.0 : dist[GOAL_NODE_ID]);
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
