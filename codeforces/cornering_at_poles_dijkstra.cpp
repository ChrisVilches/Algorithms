#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
typedef pair<double, int> pdi;
const double EPS = 1e-12;

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

struct Node {
  Point point;
  int id;
  vector<pdi> edges;
};

vector<Circle> poles;
Point robot{0, 0}, goal;
double min_dist;

bool movement_valid(Segment& s) {
  for (Circle p : poles)
    if (p.intersect(s)) return false;
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

int add_node(Point p, int pole_idx = -1) {
  int node_idx = graph.size();
  graph.push_back(Node{p, node_idx, {}});
  if (pole_idx > -1) points_in_pole[pole_idx].push_back(node_idx);
  return node_idx;
}

void solve() {
  node_id = 0;
  graph.clear();
  Segment direct_robot_goal{robot, goal};

  if (movement_valid(direct_robot_goal)) {
    min_dist = direct_robot_goal.length();
    return;
  }

  for (int i = 0; i < (int)poles.size(); i++) points_in_pole[i] = vector<int>();

  const int ROBOT_NODE_ID = add_node(robot);
  const int GOAL_NODE_ID = add_node(goal);

  for (int i = 0; i < (int)poles.size(); i++) {
    for (Segment& tangent : poles[i].tangents_from_point(robot))
      if (movement_valid(tangent)) {
        int n = add_node(tangent.q, i);
        graph[ROBOT_NODE_ID].edges.emplace_back(tangent.length(), n);
      }

    for (Segment& tangent : poles[i].tangents_from_point(goal))
      if (movement_valid(tangent)) {
        int n = add_node(tangent.q, i);
        graph[n].edges.emplace_back(tangent.length(), GOAL_NODE_ID);
      }

    for (int j = i + 1; j < (int)poles.size(); j++)
      for (Segment& tangent : poles[i].tangents_to(poles[j]))
        if (movement_valid(tangent)) {
          int n1 = add_node(tangent.p, i);
          int n2 = add_node(tangent.q, j);
          graph[n1].edges.emplace_back(tangent.length(), n2);
          graph[n2].edges.emplace_back(tangent.length(), n1);
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

        array<pair<Segment, Segment>, 2> tangent_combinations{
            make_pair(Segment{in_pt + center.to(in_pt).rot_ccw(), in_pt},
                      Segment{out_pt, out_pt + center.to(out_pt).rot_cw()}),
            make_pair(Segment{in_pt + center.to(in_pt).rot_cw(), in_pt},
                      Segment{out_pt, out_pt + center.to(out_pt).rot_ccw()})};

        for (pair<Segment, Segment> combination : tangent_combinations) {
          auto [in_tan, out_tan] = combination;
          if (!arc_intersect_any_circle(i, in_tan, out_tan)) {
            double arc = poles[i].arc(in_tan, out_tan);
            graph[p1].edges.emplace_back(arc, p2);
            graph[p2].edges.emplace_back(arc, p1);
          }
        }
      }
  }

  vector<double> dist(graph.size(), DBL_MAX);

  priority_queue<pdi, vector<pdi>, greater<pdi>> q;

  q.emplace(0, ROBOT_NODE_ID);
  dist[ROBOT_NODE_ID] = 0;

  while (!q.empty()) {
    auto [_, u] = q.top();
    q.pop();
    for (auto [weight, v] : graph[u].edges) {
      double alt = dist[u] + weight;
      if (alt < dist[v]) {
        dist[v] = alt;
        q.emplace(alt, v);
      }
    }
  }

  min_dist = dist[GOAL_NODE_ID];
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
