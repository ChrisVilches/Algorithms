#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld EPS = 1e-9;

struct Point {
  ld x, y;
  inline Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  inline Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline ld operator^(const Point& p) const { return (x * p.y) - (y * p.x); }
  inline Point to(const Point& p) const { return p - *this; }
  inline Point scale(ld f) { return Point{x * f, y * f}; }
  inline ld operator*(const Point& p) const { return (x * p.x) + (y * p.y); }
  bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : (*this ^ p) > 0;
  }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
  static Point from_stdin() {
    Point p;
    cin >> p.x >> p.y;
    return p;
  }
};

struct Segment {
  Point p, q;
  Segment scale(ld f) const { return Segment{p, p + p.to(q).scale(f)}; }

  pair<bool, Point> intersect_non_collinear(const Segment& s) const {
    const bool o1 = orientation(p, q, s.p) != orientation(p, q, s.q);
    const bool o2 = orientation(s.p, s.q, p) != orientation(s.p, s.q, q);
    return o1 && o2 ? make_pair(true, intersection_point(s)) : make_pair(false, Point{});
  }

 private:
  int orientation(const Point& p, const Point& q, const Point& r) const {
    ld val = (q - p) ^ (r - p);
    if (fabs(val) < EPS) return 0;
    return val > 0 ? 1 : -1;
  }

  Point intersection_point(const Segment& s) const {
    const ld s1_x = q.x - p.x;
    const ld s1_y = q.y - p.y;
    const ld s2_x = s.q.x - s.p.x;
    const ld s2_y = s.q.y - s.p.y;
    const ld t =
        (s2_x * (p.y - s.p.y) - s2_y * (p.x - s.p.x)) / (-s2_x * s1_y + s1_x * s2_y);
    return {p.x + (t * s1_x), p.y + (t * s1_y)};
  }
};

bool point_inside_polygon(const Point& p, const vector<Point>& polygon) {
  for (int i = 0; i < (int)polygon.size(); i++)
    if ((polygon[i].to(polygon[(i + 1) % (int)polygon.size()]) ^ polygon[i].to(p)) <= 0)
      return false;

  return true;
}

Point point_set_centroid(const vector<Point>& points) {
  Point centroid{0, 0};

  for (const Point& p : points) {
    centroid.x += p.x / (ld)points.size();
    centroid.y += p.y / (ld)points.size();
  }

  return centroid;
}

vector<Point> sort_vertices(vector<Point> polygon_vertices) {
  Point centroid = point_set_centroid(polygon_vertices);
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
      const Segment edge1{p1[i], p1[(i + 1) % (int)p1.size()]};
      const Segment edge2{p2[j], p2[(j + 1) % (int)p2.size()]};
      const auto [intersect, point] = edge1.intersect_non_collinear(edge2);
      if (intersect) result.push_back(point);
    }
  }

  return sort_vertices(result);
}

ld polygon_area(const vector<Point>& polygon) {
  ld total = 0;

  for (int i = 1; i < (int)polygon.size() - 1; i++)
    total += fabs(polygon[0].to(polygon[i]) ^ polygon[0].to(polygon[i + 1])) / 2.0;

  return total;
}

int main() {
  int N;

  while (cin >> N && N) {
    vector<Point> polygon1(N);
    for (int i = 0; i < N; i++) polygon1[i] = Point::from_stdin();

    cin >> N;

    vector<Point> polygon2(N);
    for (int i = 0; i < N; i++) polygon2[i] = Point::from_stdin();

    // Convert to counter clockwise.
    reverse(polygon1.begin(), polygon1.end());
    reverse(polygon2.begin(), polygon2.end());

    vector<Point> intersection = polygon_intersection(polygon1, polygon2);

    ld area1 = polygon_area(polygon1);
    ld area2 = polygon_area(polygon2);
    ld intersection_area = polygon_area(intersection);

    ld ans = fabs(area1 + area2 - 2 * intersection_area);

    stringstream ss;
    ss << fixed << setprecision(2) << ans;
    printf("%*s%.2Lf", 8 - (int)ss.str().size(), "", ans);
  }

  putchar('\n');
}
