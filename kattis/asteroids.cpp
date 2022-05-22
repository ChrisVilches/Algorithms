#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld EPS = 1e-9;

struct Segment;

struct Point {
  ld x, y;
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  ld cross(const Point& p) const { return x * p.y - y * p.x; }
  Point to(const Point& p) const { return p - *this; }
  Point scale(ld f) { return {x * f, y * f}; }
  ld operator*(const Point& p) const { return x * p.x + y * p.y; }
  ld dist(const Point& p) const { return hypot(x - p.x, y - p.y); }
  bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
  void operator+=(const Point& p) {
    x += p.x;
    y += p.y;
  }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
  ld dist(const Segment& s) const;
};

struct Segment {
  Point p, q;
  Segment scale(const ld f) const { return {p, p + p.to(q).scale(f)}; }

  Segment operator+(const Point& a) const { return {p + a, q + a}; }

  pair<bool, Point> intersect_non_collinear(const Segment& s) const {
    const ld o1 = orientation(p, q, s.p) != orientation(p, q, s.q);
    const ld o2 = orientation(s.p, s.q, p) != orientation(s.p, s.q, q);
    return o1 && o2 ? make_pair(true, intersection_point(s)) : make_pair(false, Point{});
  }

 private:
  int orientation(const Point& p, const Point& q, const Point& r) const {
    ld val = (q - p).cross(r - p);
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

Point project_point_segment(const Segment& s, const Point c) {
  const Point p = s.p;
  const Point q = s.q;
  ld r = p.to(q) * p.to(q);
  if (fabs(r) < EPS) return p;
  r = (p.to(c) * p.to(q)) / r;
  if (r < 0) return p;
  if (r > 1) return q;
  return p + p.to(q).scale(r);
}

ld Point::dist(const Segment& s) const { return dist(project_point_segment(s, *this)); }

bool point_inside_polygon(const Point& p, const vector<Point>& polygon) {
  const int n = polygon.size();
  for (int i = 0; i < (int)polygon.size(); i++)
    if ((polygon[i].to(polygon[(i + 1) % n]).cross(polygon[i].to(p))) <= 0) return false;

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

  for (int i = 0; i < (int)polygon.size(); i++)
    total += polygon[i].cross(polygon[(i + 1) % (int)polygon.size()]);

  return total / 2;
}

vector<Point> move(vector<Point> polygon, Point v, const ld t) {
  v = v.scale(t);
  for (Point& p : polygon) p += v;
  return polygon;
}

int main() {
  int N;

  while (cin >> N) {
    Point v1, v2;
    vector<Point> polygon1(N);
    for (int i = 0; i < N; i++) cin >> polygon1[i].x >> polygon1[i].y;
    cin >> v1.x >> v1.y;

    cin >> N;

    vector<Point> polygon2(N);
    for (int i = 0; i < N; i++) cin >> polygon2[i].x >> polygon2[i].y;
    cin >> v2.x >> v2.y;

    reverse(polygon1.begin(), polygon1.end());
    reverse(polygon2.begin(), polygon2.end());

    ld lowest_time = DBL_MAX;

    for (int s = 0; s < 2; s++) {
      for (int i = 0; i < (int)polygon1.size(); i++) {
        for (int j = 0; j < (int)polygon2.size(); j++) {
          const Segment edge{polygon2[j], polygon2[(j + 1) % (int)polygon2.size()]};

          ld lo = 0;
          ld hi = 100000;

          for (int it = 0; it < 150; it++) {
            const ld third = (hi - lo) / 3;
            const ld t1 = lo + third;
            const ld t2 = hi - third;

            const ld dist1 = (polygon1[i] + v1.scale(t1)).dist(edge + v2.scale(t1));
            const ld dist2 = (polygon1[i] + v1.scale(t2)).dist(edge + v2.scale(t2));

            if (dist1 < EPS) lowest_time = min(lowest_time, t1);
            if (dist2 < EPS) lowest_time = min(lowest_time, t2);

            if (dist1 > dist2)
              lo = t1;
            else
              hi = t2;
          }
        }
      }
      swap(v1, v2);
      swap(polygon1, polygon2);
    }

    if (lowest_time == DBL_MAX) {
      cout << "never" << endl;
      continue;
    }

    auto intersection_area = [&](const ld t) -> ld {
      return polygon_area(
          polygon_intersection(move(polygon1, v1, t), move(polygon2, v2, t)));
    };

    ld lo = lowest_time;
    ld hi = 100000;

    for (int it = 0; it < 150; it++) {
      const ld third = (hi - lo) / 3;
      const ld t1 = lo + third;
      const ld t2 = hi - third;

      const ld a1 = intersection_area(t1);
      const ld a2 = intersection_area(t2);

      if (fabs(a1 - a2) < EPS || a1 > a2)
        hi = t2;
      else
        lo = t1;
    }

    cout << fixed << setprecision(6) << lo << endl;
  }
}
