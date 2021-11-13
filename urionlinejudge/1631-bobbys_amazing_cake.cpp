#include <bits/stdc++.h>

using namespace std;

struct Point {
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
  bool operator<(const Point& p) const {
    if (y == p.y) return x < p.x;
    return y < p.y;
  }

  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
};

struct Line {
  double a, b, c;

  Line(double a, double b, double c) : a(a), b(b), c(c) {}

  double distance(Point& p) {
    return fabs(a * p.x + b * p.y + c) / (sqrt(a * a + b * b));
  }

  static Line from_two_points(Point& p, Point& q) {
    double a = q.y - p.y;
    double b = p.x - q.x;
    double c = a * (p.x) + b * (p.y);
    return Line(a, b, c);
  }
};

int cross_product(Point& O, Point& A, Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

int N;

void solve() {
  vector<Point> points;

  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    points.push_back(Point(x, y));
  }

  double diff = DBL_MAX;

  for (int i = 0; i < N; i++) {
    vector<Point> p2;
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      p2.push_back(points[j] - points[i]);
    }

    for (int j = 0; j < (int)p2.size(); j++) {
      double side1 = 0;
      double side2 = 0;

      Point zero(0, 0);

      Line line = Line::from_two_points(zero, p2[j]);

      bool iter = false;

      for (Point& p : p2) {
        double dist = line.distance(p);
        if (fabs(dist) < 0.001) continue;

        iter = true;
        double side = cross_product(zero, p2[j], p);

        if (side > 0)
          side1 += dist;
        else
          side2 += dist;
      }

      if (iter) diff = min(diff, fabs(side1 - side2));
    }
  }

  for (int i = 0; i < N; i++) {
    break;
    for (int j = 0; j < N; j++) {
      if (i == j) continue;

      double side1 = 0;
      double side2 = 0;

      Line line = Line::from_two_points(points[i], points[j]);

      for (Point& p : points) {
        double dist = line.distance(p);
        double side = cross_product(points[i], points[j], p);

        if (side > 0)
          side1 += dist;
        else
          side2 += dist;
      }

      diff = min(diff, fabs(side1 - side2));
    }
  }

  if (diff == DBL_MAX) diff = 0;

  printf("%.3f\n", diff);
}

int main() {
  while (scanf("%d", &N) == 1 && N > 0) solve();
}
