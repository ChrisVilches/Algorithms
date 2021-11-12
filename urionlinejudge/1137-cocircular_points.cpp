#include <bits/stdc++.h>

using namespace std;

int N;

struct Point {
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
  Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
  double dist(const Point& p) const {
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
  }
};

struct Circle {
  Point center;
  double radius;
  Circle(Point c, double r) : center(c), radius(r) {}
};

Point center_from(double bx, double by, double cx, double cy) {
  double B = bx * bx + by * by, C = cx * cx + cy * cy, D = bx * cy - by * cx;
  return Point((cy * B - by * C) / (2 * D), (bx * C - cx * B) / (2 * D));
}

Circle circle_from(Point A, Point B, Point C) {
  Point c = A + center_from(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);
  return Circle(c, c.dist(A));
}

double cross_product(Point& O, Point& A, Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

void solve() {
  vector<Point> points;

  for (int i = 0; i < N; i++) {
    double x, y;
    cin >> x >> y;
    points.push_back(Point(x, y));
  }

  if (N <= 2) {
    cout << N << endl;
    return;
  }

  int ans = 0;

  for (int i = 0; i < N; i++)
    for (int j = i + 1; j < N; j++)
      for (int k = j + 1; k < N; k++) {
        if (cross_product(points[i], points[j], points[k]) == 0) {
          ans = max(ans, 2);
          continue;
        }

        Circle circle = circle_from(points[i], points[j], points[k]);

        int count = 0;

        for (int p = 0; p < N; p++)
          if (fabs(circle.center.dist(points[p]) - circle.radius) < 0.000001)
            count++;

        ans = max(ans, count);
      }

  cout << ans << endl;
}

int main() {
  while (scanf("%d", &N) == 1 && N > 0) solve();
}
