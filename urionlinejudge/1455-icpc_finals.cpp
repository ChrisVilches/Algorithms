#include <bits/stdc++.h>

using namespace std;

int N;

struct Point {
  double x, y;
  Point operator+(const Point& p) const { return Point{x + p.x, y + p.y}; }
  double dist(const Point& p) const { return hypot(x - p.x, y - p.y); }
  Point mid_point(const Point& p) const { return {(x + p.x) / 2.0, (y + p.y) / 2.0}; }
  bool operator<(const Point& p) const {
    if (y == p.y) return x < p.x;
    return y < p.y;
  }
};

struct Circle {
  Point center;
  double radius;
  bool operator<(const Circle& c) const { return radius < c.radius; }
};

Point center_from(double bx, double by, double cx, double cy) {
  double B = bx * bx + by * by, C = cx * cx + cy * cy, D = bx * cy - by * cx;
  return Point{(cy * B - by * C) / (2 * D), (bx * C - cx * B) / (2 * D)};
}

Circle circle_from(const Point& A, const Point& B, const Point& C) {
  Point c = A + center_from(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);
  return Circle{c, c.dist(A)};
}

Circle circle_from(const Point& A, const Point& B) {
  Point mid = A.mid_point(B);
  double radius = A.dist(B) / 2.0;
  return Circle{mid, radius};
}

double cross_product(const Point& O, const Point& A, const Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point>& A) {
  int n = A.size(), k = 0;
  if (n <= 3) return A;
  vector<Point> ans(2 * n);
  sort(A.begin(), A.end());
  for (int i = 0; i < n; ++i) {
    while (k >= 2 && cross_product(ans[k - 2], ans[k - 1], A[i]) <= 0) k--;
    ans[k++] = A[i];
  }
  for (int i = n - 1, t = k + 1; i > 0; --i) {
    while (k >= t && cross_product(ans[k - 2], ans[k - 1], A[i - 1]) <= 0) k--;
    ans[k++] = A[i - 1];
  }
  ans.resize(k - 1);
  return ans;
}

void solve() {
  vector<Point> points(N);

  for (int i = 0; i < N; i++) {
    cin >> points[i].x >> points[i].y;
  }

  points = convex_hull(points);
  N = points.size();

  Circle ans{Point{0, 0}, 1e15};

  auto try_circle = [&](const Circle& circle) {
    if (ans < circle) return;

    for (const Point& p : points)
      if (p.dist(circle.center) - 1e-12 > circle.radius) return;

    ans = min(ans, circle);
  };

  try_circle(circle_from(points.front(), points.back()));

  for (int i = 0, j = 1; i < N; i++) {
    for (; j < N; j++) {
      const double dist = points[i].dist(points[j]);
      const double next_dist = points[i].dist(points[(j + 1) % N]);
      if (next_dist > dist) continue;

      try_circle(circle_from(points[i], points[j]));
      break;
    }
  }

  for (int i = 0; i < N; i++)
    for (int j = i + 1; j < N; j++)
      for (int k = j + 1; k < N; k++)
        try_circle(circle_from(points[i], points[j], points[k]));

  cout << fixed << setprecision(2) << ans.center.x << ' ' << ans.center.y << ' '
       << ans.radius << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int test_n = 1;
  while (cin >> N && N) {
    cout << "Instancia " << test_n++ << endl;
    solve();
    cout << '\n';
  }
}
