#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
  Point() {}

  bool operator<(Point p) {
    if (y == p.y) return x < p.x;
    return y < p.y;
  }
};

int cross(Point& O, Point& A, Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point>& A) {
  int n = A.size(), k = 0;
  if (n <= 3) return A;
  vector<Point> ans(2 * n);
  sort(A.begin(), A.end());
  for (int i = 0; i < n; ++i) {
    while (k >= 2 && cross(ans[k - 2], ans[k - 1], A[i]) <= 0) k--;
    ans[k++] = A[i];
  }
  for (int i = n - 1, t = k + 1; i > 0; --i) {
    while (k >= t && cross(ans[k - 2], ans[k - 1], A[i - 1]) <= 0) k--;
    ans[k++] = A[i - 1];
  }
  ans.resize(k - 1);
  return ans;
}

int main() {
  while (true) {
    bool all_zero = true;

    vector<Point> points;
    for (int i = 0; i < 5; i++) {
      int x, y;
      cin >> x >> y;
      points.push_back(Point(x, y));

      if (x != 0 || y != 0) all_zero = false;
    }

    if (all_zero) break;

    vector<int> perm{0, 1, 2, 3, 4};

    long double ans = 0;

    do {
      vector<Point> p;
      p.push_back(points[perm[0]]);
      p.push_back(points[perm[1]]);
      p.push_back(points[perm[2]]);
      p.push_back(points[perm[3]]);

      vector<Point> hull = convex_hull(p);

      if (hull.size() != 4) continue;

      long double area = 0;

      for (int i = 2; i < (int)hull.size(); i++)
        area += fabs(cross(hull[0], hull[i], hull[i - 1])) / 2L;

      ans = max(ans, area);

    } while (next_permutation(perm.begin(), perm.end()));

    printf("%.0Lf\n", ans);
  }
}
