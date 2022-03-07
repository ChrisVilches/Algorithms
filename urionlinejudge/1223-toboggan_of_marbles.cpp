#include <bits/stdc++.h>

using namespace std;

double EPS = 1e-12;

// Segment to segment distance.

struct Segment;

struct Point {
  double x, y;
  Point operator+(const Point& p) { return Point{x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
  Point scale(double f) { return Point{x * f, y * f}; }
  Point to(const Point& p) const { return p - *this; }
  double operator*(const Point& p) { return x * p.x + y * p.y; }
  double dist(const Point& p) { return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2)); }
  double dist(Segment& s);
};

struct Segment {
  Point p, q;

  double dist(Segment& s) {
    return min({s.p.dist(*this), s.q.dist(*this), p.dist(s), q.dist(s)});
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

  vector<Segment> flaps(N);

  for (int i = 0; i < N; i++) {
    double yi, xf, yf;
    cin >> yi >> xf >> yf;
    flaps[i].p.x = i % 2 == 0 ? 0 : L;
    flaps[i].p.y = yi;
    flaps[i].q.x = xf;
    flaps[i].q.y = yf;
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
