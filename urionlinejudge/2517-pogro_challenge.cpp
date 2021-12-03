#include <bits/stdc++.h>

using namespace std;

struct Point {
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
  Point() {}
  double dist(const Point& p) const {
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
  }
};

double A, B, C, xf;

inline double f(double x) { return -(pow(x, 2) / A) - (x / B) + C; }

void solve() {
  Point camera;
  cin >> camera.x >> camera.y >> xf;

  double left = 0;
  double right = xf;

  int iters = 100;

  while (iters--) {
    double third = (right - left) / 3;
    double x1 = left + third;
    double x2 = right - third;

    if (camera.dist(Point(x1, f(x1))) > camera.dist(Point(x2, f(x2))))
      left = x1;
    else
      right = x2;
  }

  printf("%.2f\n", camera.dist(Point(left, f(left))));
}

int main() {
  while (scanf("%lf %lf %lf", &A, &B, &C) == 3) solve();
}
