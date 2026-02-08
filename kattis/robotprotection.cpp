#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  int cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
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

  while (cin >> n && n > 0) {
    vector<Point> points(n);
    for (auto& p : points) cin >> p.x >> p.y;

    const vector<Point> hull = convex_hull(points);

    n = hull.size();
    double area = 0;

    for (int i = n - 1, j = 0; j < n; i = j++) {
      const Point p = hull[i];
      const Point q = hull[j];
      area += p.cross(q);
    }

    area /= 2;

    cout << area << endl;
  }
}
