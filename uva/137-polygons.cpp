#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

struct Point {
  ld x, y;
  inline Point operator+(const Point& p) const { return Point{x + p.x, y + p.y}; }
  inline Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
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

  bool intersect(const Segment& s) const {
    Point p1 = p, p2 = s.p;
    Point q1 = q, q2 = s.q;
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    return o1 != o2 && o3 != o4;
  }

 private:
  int orientation(Point p, Point q, Point r) const {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    return val < 0 ? -1 : val > 0;
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
  return polygon_vertices;
}

vector<Point> polygon_intersection_origin_center(const vector<Point>& p1,
                                                 const vector<Point>& p2) {
  vector<Point> result;

  for (const Point& p : p1)
    if (point_inside_polygon(p, p2)) result.push_back(p);

  for (const Point& p : p2)
    if (point_inside_polygon(p, p1)) result.push_back(p);

  for (int i = 0; i < (int)p1.size(); i++) {
    for (int j = 0; j < (int)p2.size(); j++) {
      const Segment edge1{p1[i], p1[(i + 1) % (int)p1.size()]};
      const Segment edge2{p2[j], p2[(j + 1) % (int)p2.size()]};

      // TODO: Find intersection without using binary search.
      if (edge1.intersect(edge2)) {
        ld lo = 0.0;
        ld hi = 1.0;
        int iter = 30;

        while (iter--) {
          ld mid = (lo + hi) / 2.0;

          if (edge1.scale(mid).intersect(edge2))
            hi = mid;
          else
            lo = mid;
        }

        result.push_back(edge1.scale(lo).q);
      }
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

    vector<Point> intersection = polygon_intersection_origin_center(polygon1, polygon2);

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
