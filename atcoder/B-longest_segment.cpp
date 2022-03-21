#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

struct Point {
  ld x, y;
  bool operator<(const Point& p) const {
    if (y == p.y) return x < p.x;
    return y < p.y;
  }

  ld dist(const Point& p) const { return hypot(x - p.x, y - p.y); }
};

ld cross_product(const Point& O, const Point& A, const Point& B) {
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

pair<Point, Point> most_distant_points(vector<Point>& points) {
  const vector<Point> hull = convex_hull(points);

  ld largest_dist = 0;
  pair<Point, Point> res;

  for (int i = 0, j = 1; i < (int)hull.size(); i++) {
    for (; j < (int)hull.size(); j++) {
      const ld dist = hull[i].dist(hull[j]);
      const ld next_dist = hull[i].dist(hull[(j + 1) % hull.size()]);

      if (dist > largest_dist) {
        res = {hull[i], hull[j]};
        largest_dist = dist;
      }

      if (next_dist < dist) break;
    }
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N) {
    vector<Point> points(N);

    for (int i = 0; i < N; i++) {
      cin >> points[i].x >> points[i].y;
    }

    const auto [p, q] = most_distant_points(points);

    cout << fixed << setprecision(15) << p.dist(q) << endl;
  }
}
