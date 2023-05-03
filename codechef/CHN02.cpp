#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point() {}
  Point(const double x, const double y) : x(x), y(y) { assert(!isnan(x) && !isnan(y)); }
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  double cross(const Point p) const { return x * p.y - y * p.x; }
  Point scale(const double f) const { return {x * f, y * f}; }
  double magnitude() const { return hypot(x, y); }
  Point normalize() const { return {x / magnitude(), y / magnitude()}; }
  bool operator<(const Point p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
};

short orientation(const Point p, const Point q, const Point u, const Point v) {
  const double cross = (q - p).cross(v - u);
  return cross < 0 ? -1 : cross > 0;
}

struct Segment {
  Point p, q;
  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }
  bool parallel(const Segment s) const { return orientation(p, q, s.p, s.q) == 0; }
  Point intersection_point(const Segment s) const {
    const double factor = (s.q - s.p).cross(p - s.p) / (q - p).cross(s.q - s.p);
    return scale(factor).q;
  }
};

short orientation(const Segment s, const Segment r) {
  return orientation(s.p, s.q, r.p, r.q);
}

short orientation(const Segment s, const Point p) {
  return orientation(s.p, s.q, s.p, p);
}

vector<Segment> create_half_planes(const vector<vector<Point>>& polygons) {
  vector<Segment> half_planes;

  for (const vector<Point>& polygon : polygons) {
    for (int i = 0; i < (int)polygon.size(); i++) {
      const Point p = polygon[i];
      const Point q = polygon[(i + 1) % polygon.size()];
      const Point dir = (q - p).normalize();
      half_planes.push_back({p, p + dir});
    }
  }

  sort(half_planes.begin(), half_planes.end(),
       [](const Segment s, const Segment r) { return (s.q - s.p) < (r.q - r.p); });
  return half_planes;
}

bool can_add(const deque<Segment>& edges, const Segment half_plane) {
  if (edges.size() <= 2) return true;
  if (orientation(edges[0], edges.back()) >= 0) return true;
  return orientation(half_plane, edges.back().intersection_point(edges[0])) == -1;
}

bool empty_intersection(const deque<Segment>& edges) {
  return edges.size() >= 2 && orientation(edges[edges.size() - 2], edges.back()) <= 0;
}

void remove_back(deque<Segment>& edges, const Segment half_plane) {
  while (edges.size() >= 2) {
    const Point prev_vertex = edges[edges.size() - 2].intersection_point(edges.back());
    if (orientation(half_plane, prev_vertex) <= 0) {
      edges.pop_back();
    } else {
      break;
    }
  }
}

void remove_front(deque<Segment>& edges) {
  while (edges.size() >= 2 && orientation(edges.back(), edges[0]) > 0 &&
         orientation(edges.back(), edges[0].intersection_point(edges[1])) <= 0)
    edges.pop_front();
}

vector<Segment> create_polygon_edges(const vector<Segment>& half_planes) {
  deque<Segment> edges;

  for (const Segment half_plane : half_planes) {
    if (!edges.empty() && edges.back().parallel(half_plane)) {
      if (orientation(edges.back(), half_plane.p) >= 0) {
        edges.pop_back();
      } else {
        continue;
      }
    }

    remove_back(edges, half_plane);
    if (can_add(edges, half_plane)) edges.push_back(half_plane);
    if (empty_intersection(edges)) return {};
    remove_front(edges);
  }

  return vector<Segment>{edges.begin(), edges.end()};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N;

  while (cin >> N) {
    vector<vector<Point>> polygons(N);

    for (vector<Point>& polygon : polygons) {
      int C;
      cin >> C;
      polygon = vector<Point>(C);
      for (Point& p : polygon) cin >> p.x >> p.y;
    }

    const vector<Segment> half_planes = create_half_planes(polygons);
    const vector<Segment> edges = create_polygon_edges(half_planes);

    vector<Point> vertices;

    for (int i = 0; i < (int)edges.size(); i++) {
      const Segment edge1 = edges[i];
      const Segment edge2 = edges[(i + 1) % edges.size()];
      vertices.push_back(edge1.intersection_point(edge2));
    }

    double area = 0;

    for (int i = 0; i < (int)vertices.size(); i++) {
      const Point p = vertices[i];
      const Point q = vertices[(i + 1) % vertices.size()];
      area += p.cross(q) / 2;
    }

    cout << fixed << setprecision(8) << area << endl;
  }
}
