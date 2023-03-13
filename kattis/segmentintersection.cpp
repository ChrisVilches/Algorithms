#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  double cross(const Point& p) const { return x * p.y - y * p.x; }
  Point scale(const double f) const { return {x * f, y * f}; }
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
  double operator*(const Point& p) const { return x * p.x + y * p.y; }

  bool operator<(const Point p) const {
    if (x != p.x) return x < p.x;
    return y < p.y;
  }
};

short orientation(const Point& o, const Point& a, const Point& b) {
  const double cross = (a - o).cross(b - o);
  return cross < 0 ? -1 : cross > 0;
}

struct Segment {
  Point p, q;

  vector<Point> all_intersections(const Segment& s) const {
    set<Point> intersections;

    if (contains(s.p)) intersections.emplace(s.p);
    if (contains(s.q)) intersections.emplace(s.q);
    if (s.contains(p)) intersections.emplace(p);
    if (s.contains(q)) intersections.emplace(q);

    const auto [intersect, p] = intersect_non_collinear(s);
    if (intersect) {
      intersections.emplace(p);
    }

    return vector<Point>(intersections.begin(), intersections.end());
  }

 private:
  Segment scale(const double f) const { return {p, p + (q - p).scale(f)}; }

  bool intersect(const Segment& s) const {
    const short o1 = orientation(p, q, s.p);
    const short o2 = orientation(p, q, s.q);
    const short o3 = orientation(s.p, s.q, p);
    const short o4 = orientation(s.p, s.q, q);
    return o1 * o2 < 0 && o3 * o4 < 0;
  }

  pair<bool, Point> intersect_non_collinear(const Segment& s) const {
    return intersect(s) ? make_pair(true, intersection_point(s))
                        : make_pair(false, Point{});
  }

  Point intersection_point(const Segment& s) const {
    const double factor = (s.q - s.p).cross(p - s.p) / (q - p).cross(s.q - s.p);
    return scale(factor).q;
  }

  bool contains_except_endpoints(const Point& r) const {
    if (orientation(p, q, r) != 0) return false;
    return (q - p) * (r - p) > 0 && (p - q) * (r - q) > 0;
  }

  bool contains(const Point& r) const {
    return p == r || q == r || contains_except_endpoints(r);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  while (T--) {
    Segment s, r;
    cin >> s.p.x >> s.p.y;
    cin >> s.q.x >> s.q.y;
    cin >> r.p.x >> r.p.y;
    cin >> r.q.x >> r.q.y;

    const vector<Point> res = s.all_intersections(r);

    if (res.empty()) {
      cout << "none" << endl;
    }

    for (const Point p : res) {
      cout << fixed << setprecision(2) << p.x << " " << p.y << " ";
    }

    cout << '\n';
  }
}
