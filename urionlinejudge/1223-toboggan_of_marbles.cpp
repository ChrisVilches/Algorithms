#include <bits/stdc++.h>

using namespace std;

double EPS = 1e-12;

// Segment to segment distance.

struct Segment;

struct Point {
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
  Point() {}
  Point operator+(const Point& p) { return Point(x + p.x, y + p.y); }
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  inline double operator^(const Point& p) const {
    return (x * p.y) - (y * p.x);
  }
  Point scale(double f) { return Point(x * f, y * f); }
  Point to(const Point& p) const { return p - *this; }
  double operator*(const Point& p) { return x * p.x + y * p.y; }
  double dist(const Point& p) {
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
  }
  double dist(Segment& s);
};

struct Segment {
  Point p, q;
  Segment(Point p, Point q) : p(p), q(q) {}
  Segment() {}

  double dist(Segment& s) {
    if (intersect(s)) return 0;
    return min({s.p.dist(*this), s.q.dist(*this), p.dist(s), q.dist(s)});
  }

  int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
  }

  bool intersect(const Segment& s) {
    Point p1 = p;
    Point q1 = q;
    Point p2 = s.p;
    Point q2 = s.q;
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    return (o1 != o2 && o3 != o4);
  }
};

Point project_point_segment(Segment& s, Point c) {
  Point p = s.p;
  Point q = s.q;
  double r = p.to(q) * p.to(q);
  if (fabs(r) < EPS) return p;
  r = (p.to(c) * p.to(q)) / r;
  if (r < 0) return p;
  if (r > 1) return q;
  return p + p.to(q).scale(r);
}

double Point::dist(Segment& s) { return dist(project_point_segment(s, *this)); }

int N;

void solve() {
  double L, H;
  cin >> L >> H;

  vector<Segment> flaps;

  for (int i = 0; i < N; i++) {
    double yi, xf, yf;
    cin >> yi >> xf >> yf;
    Point p(i % 2 == 0 ? 0 : L, yi), q(xf, yf);
    flaps.push_back(Segment(p, q));
  }

  double ans = DBL_MAX;

  for (int i = 0; i < (int)flaps.size(); i++)
    if (i % 2 == 0)
      ans = min(ans, (double)(L - flaps[i].q.x));
    else
      ans = min(ans, (double)flaps[i].q.x);

  for (int i = 0; i < (int)flaps.size() - 1; i++)
    ans = min(ans, flaps[i].dist(flaps[i + 1]));

  printf("%.2f\n", ans);
}

int main() {
  while (scanf("%d", &N) == 1) solve();
}
