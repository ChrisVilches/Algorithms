#include <bits/stdc++.h>

using namespace std;
const double EPS = 1E-9;

/**
 * Segment intersection code from:
 * https://cp-algorithms.com/geometry/segments-intersection.html
 * (The original code has more functionalities). The one from geeksforgeeks did
 * not work.
 */

struct Point {
  double x, y;

  bool operator<(const Point& p) const {
    return x < p.x - EPS || (abs(x - p.x) < EPS && y < p.y - EPS);
  }
};

struct Line {
  double a, b, c;
  Point p, q;

  Line() {}
  Line(Point p, Point q) : p(p), q(q) {
    a = p.y - q.y;
    b = q.x - p.x;
    c = -a * p.x - b * p.y;
    norm();
  }

  void norm() {
    double z = sqrt(a * a + b * b);
    if (abs(z) > EPS) a /= z, b /= z, c /= z;
  }

  double dist(Point p) const { return a * p.x + b * p.y + c; }
};

inline double det(double a, double b, double c, double d) {
  return a * d - b * c;
}

inline bool betw(double l, double r, double x) {
  return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

inline bool intersect_1d(double a, double b, double c, double d) {
  if (a > b) swap(a, b);
  if (c > d) swap(c, d);
  return max(a, c) <= min(b, d) + EPS;
}

bool intersect(Point a, Point b, Point c, Point d) {
  if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
    return false;
  Line m(a, b), n(c, d);
  double zn = det(m.a, m.b, n.a, n.b);
  if (abs(zn) < EPS)
    return !(abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS);
  else {
    double x = -det(m.c, m.b, n.c, n.b) / zn;
    double y = -det(m.a, m.c, n.a, n.c) / zn;
    return betw(a.x, b.x, x) && betw(a.y, b.y, y) && betw(c.x, d.x, x) &&
           betw(c.y, d.y, y);
  }
}

bool intersect(Line a, Line b) { return intersect(a.p, a.q, b.p, b.q); }

int N;
Line lines[51];

void solve() {
  for (int i = 0; i < N; i++) {
    Point p1, p2;
    scanf("%lf %lf %lf %lf\n", &p1.x, &p1.y, &p2.x, &p2.y);
    lines[i] = Line(p1, p2);
  }

  int total = 0;

  for (int i = 0; i < N; i++)
    for (int j = i + 1; j < N; j++)
      for (int k = j + 1; k < N; k++)
        total += intersect(lines[i], lines[j]) &&
                 intersect(lines[j], lines[k]) && intersect(lines[i], lines[k]);

  printf("%d\n", total);
}

int main() {
  while (scanf("%d", &N) && N) solve();
}
