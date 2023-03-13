#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  double cross(const Point& p) const { return x * p.y - y * p.x; }

  Point rot_ccw(const double t) const {
    return {x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)};
  }
};

short orientation(const Point& o, const Point& a, const Point& b) {
  const double cross = (a - o).cross(b - o);
  return cross < 0 ? -1 : cross > 0;
}

struct Segment {
  Point p, q;

  bool intersect(const Segment& s) const {
    const bool o1 = orientation(p, q, s.p) * orientation(p, q, s.q) < 0;
    const bool o2 = orientation(s.p, s.q, p) * orientation(s.p, s.q, q) < 0;
    return o1 && o2;
  }
};

Segment edge_at(const vector<Point>& polygon, const int i) {
  const int n = (int)polygon.size();
  return Segment{polygon[i], polygon[(i + 1) % n]};
}

bool point_inside_polygon(const Point& p, const vector<Point>& polygon) {
  const Segment ray{p, {1e7, 1e7 + 1e-4}};

  int intersections = 0;

  for (int i = 0; i < (int)polygon.size(); i++) {
    const Segment edge = edge_at(polygon, i);
    intersections += edge.intersect(ray);
  }

  return intersections % 2 == 1;
}

bool contained(const vector<Point>& inside, const vector<Point>& container) {
  for (int i = 0; i < (int)inside.size(); i++) {
    for (int j = 0; j < (int)container.size(); j++) {
      if (edge_at(inside, i).intersect(edge_at(container, j))) return false;
    }
  }

  for (const Point p : inside) {
    if (!point_inside_polygon(p, container)) return false;
  }

  return true;
}

int calculate(const vector<Point>& inside, const vector<Point>& container) {
  for (int deg = 0; deg < 360; deg++) {
    vector<Point> rotated_polygon = inside;

    for (Point& p : rotated_polygon) {
      p = p.rot_ccw(2 * M_PI * (double)deg / 360);
    }

    if (contained(rotated_polygon, container)) {
      return deg;
    }
  }

  return -1;
}

int main() {
  int N, M;

  while (cin >> N >> M) {
    vector<Point> inside(N);
    vector<Point> container(M);
    for (Point& p : inside) cin >> p.x >> p.y;
    for (Point& p : container) cin >> p.x >> p.y;

    const int ans = calculate(inside, container);

    if (ans == -1) {
      cout << "impossible" << endl;
    } else {
      cout << ans << endl;
    }
  }
}
