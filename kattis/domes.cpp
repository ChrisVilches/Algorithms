#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  double cross(const Point& p) const { return x * p.y - y * p.x; }
  double operator*(const Point& p) const { return x * p.x + y * p.y; }
  Point scale(const double f) const { return {x * f, y * f}; }
  Point rot_ccw() const { return {-y, x}; }
  double magnitude() const { return hypot(x, y); }
  Point normalize() const { return {x / magnitude(), y / magnitude()}; }

  bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
  void operator+=(const Point& p) {
    x += p.x;
    y += p.y;
  }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
};

struct Segment {
  Point p, q;
  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }

  pair<bool, Point> intersect_non_collinear(const Segment& s) const {
    return intersect(s) ? make_pair(true, intersection_point(s))
                        : make_pair(false, Point{});
  }

  bool contains(const Point& r) const {
    if (orientation(p, q, r) != 0) return false;
    return (q - p) * (r - p) > 0 && (p - q) * (r - q) > 0;
  }

 private:
  bool intersect(const Segment& s) const {
    return (orientation(p, q, s.p) * orientation(p, q, s.q) < 0) &&
           (orientation(s.p, s.q, p) * orientation(s.p, s.q, q) < 0);
  }

  short orientation(const Point& o, const Point& a, const Point& b) const {
    const double cross = (a - o).cross(b - o);
    return cross < 0 ? -1 : cross > 0;
  }

  Point intersection_point(const Segment& s) const {
    const double factor = (s.q - s.p).cross(p - s.p) / (q - p).cross(s.q - s.p);
    return scale(factor).q;
  }
};

bool point_inside_polygon(const Point& p, const vector<Point>& polygon) {
  const int n = polygon.size();

  if (n == 0) return false;

  for (int i = 0; i < n; i++) {
    const Segment edge{polygon[i], polygon[(i + 1) % n]};
    if (edge.contains(p)) return true;
  }

  for (int i = 0; i < n; i++)
    if ((polygon[(i + 1) % n] - polygon[i]).cross(p - polygon[i]) <= 0) return false;

  return true;
}

Point point_set_centroid(const vector<Point>& points) {
  Point centroid{0, 0};
  for (const Point& p : points) centroid += p.scale(1 / (double)points.size());
  return centroid;
}

vector<Point> sort_vertices(vector<Point> polygon_vertices) {
  const Point centroid = point_set_centroid(polygon_vertices);
  for (Point& p : polygon_vertices) p = p - centroid;
  sort(polygon_vertices.begin(), polygon_vertices.end());
  for (Point& p : polygon_vertices) p = p + centroid;
  return polygon_vertices;
}

vector<Point> polygon_intersection(const vector<Point>& p1, const vector<Point>& p2) {
  vector<Point> result;

  for (const Point& p : p1)
    if (point_inside_polygon(p, p2)) result.push_back(p);

  for (const Point& p : p2)
    if (point_inside_polygon(p, p1)) result.push_back(p);

  for (int i = 0; i < (int)p1.size(); i++) {
    for (int j = 0; j < (int)p2.size(); j++) {
      const Segment edge1{p1[i], p1[(i + 1) % p1.size()]};
      const Segment edge2{p2[j], p2[(j + 1) % p2.size()]};

      const auto [intersect, point] = edge1.intersect_non_collinear(edge2);
      if (intersect) result.push_back(point);
    }
  }

  return sort_vertices(result);
}

double polygon_area(const vector<Point>& polygon) {
  double total = 0;

  for (int i = 0; i < (int)polygon.size(); i++)
    total += polygon[i].cross(polygon[(i + 1) % polygon.size()]);

  return total / 2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  double X, Y;

  while (cin >> X >> Y >> N) {
    vector<Point> points(N);
    vector<int> permutation(N);

    for (Point& p : points) cin >> p.x >> p.y;

    for (int& p : permutation) {
      cin >> p;
      p--;
    }

    vector<vector<Point>> half_planes;

    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        const Point p = points[permutation[i]];
        const Point q = points[permutation[j]];

        const Point dir = (p - q).normalize();

        vector<Point> half_plane(4);
        half_plane[0] = q - dir.scale(1e6 / 2);
        half_plane[1] = q + dir.scale(1e6 / 2);
        half_plane[2] = half_plane[1] + dir.rot_ccw().scale(1e6);
        half_plane[3] = half_plane[2] - dir.scale(1e6);

        half_planes.push_back(half_plane);
      }
    }

    const vector<Point> region{{0, 0}, {X, 0}, {X, Y}, {0, Y}};

    const auto intersection =
        accumulate(half_planes.begin(), half_planes.end(), region, polygon_intersection);

    cout << fixed << setprecision(6) << polygon_area(intersection) << endl;
  }
}
