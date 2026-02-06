#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  int cross(const Point p) const { return x * p.y - y * p.x; }
  int dist2(const Point p) const { return pow(x - p.x, 2) + pow(y - p.y, 2); }
};

short orientation(const Point o, const Point a, const Point b) {
  const int x = (a - o).cross(b - o);
  return (x > 0) - (x < 0);
}

vector<Point> convex_hull(vector<Point> A) {
  int n = A.size(), k = 0;
  if (n <= 2) return A;
  vector<Point> res(n + 1);
  sort(A.begin(), A.end(), [](const Point p, const Point q) {
    return p.y < q.y || (p.y == q.y && p.x < q.x);
  });
  for (int i = 0; i < n; i++) {
    while (k >= 2 && orientation(res[k - 2], res[k - 1], A[i]) <= 0) k--;
    res[k++] = A[i];
  }
  for (int i = n - 1, t = k + 1; i > 0; i--) {
    while (k >= t && orientation(res[k - 2], res[k - 1], A[i - 1]) <= 0) k--;
    res[k++] = A[i - 1];
  }
  res.resize(k - 1);
  return res;
}

int main() {
  int n;
  while (cin >> n) {
    vector<Point> points(n);
    for (auto& p : points) cin >> p.x >> p.y;
    points = convex_hull(points);
    n = points.size();

    int ans = 0;
    int j = 1;

    for (const Point p : points) {
      for (; j < 2 * n; j++) {
        const int a = p.dist2(points[(j - 1 + n) % n]);
        const int b = p.dist2(points[j % n]);
        const int c = p.dist2(points[(j + 1) % n]);
        ans = max(ans, b);
        if (b > a && b > c) break;
      }
    }

    cout << fixed << setprecision(9) << sqrt(ans) << endl;
  }
}
