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

int N;

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

void solve() {
  vector<Point> points;
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    points.push_back(Point(x, y));
  }

  vector<Point> hull = convex_hull(points);

  long double total = 0;

  for (int i = 2; i < (int)hull.size(); i++)
    total += fabs(cross(hull[0], hull[i - 1], hull[i])) / 2L;

  printf("%.2Lf\n", total);
}

int main() {
  while (scanf("%d ", &N) == 1) solve();
}
