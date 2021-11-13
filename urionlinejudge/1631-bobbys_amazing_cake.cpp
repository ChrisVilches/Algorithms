#include <bits/stdc++.h>

using namespace std;

struct Point {
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
};

struct Line {
  double a, b, c;

  Line(double a, double b, double c) : a(a), b(b), c(c) {}

  double distance(Point& p) {
    return fabs(a * p.x + b * p.y + c) / (sqrt(a * a + b * b));
  }

  static Line from_vector(Point v) {
    double a = -v.y;
    double b = v.x;
    double c = a * (v.x) + b * (v.y);
    return Line(a, b, c);
  }
};

int N;

inline double cross(Point p, Point q) { return p.x * q.y - p.y * q.x; }

void solve() {
  vector<Point> points;

  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    points.push_back(Point(x, y));
  }

  double diff = DBL_MAX;

  for (int i = 0; i < N; i++) {
    for (int j = i; j < N; j++) {
      double side1 = 0;
      double side2 = 0;

      Line line = Line::from_vector(points[j] - points[i]);

      for (int k = 0; k < N; k++) {
        Point p = points[k] - points[i];
        double dist = line.distance(p);
        double side = cross(points[j] - points[i], p);

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
