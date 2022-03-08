#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

struct Point {
  ll x, y;

  bool operator<(const Point& p) const {
    if (y == p.y) return x < p.x;
    return y < p.y;
  }
};

ll cross_product(const Point& O, const Point& A, const Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

ld triangle_area(const Point& O, const Point& A, const Point& B) {
  return fabs(cross_product(O, A, B) / 2.0);
}

vector<Point> convex_hull(vector<Point>& A) {
  int n = A.size(), k = 0;
  if (n <= 3) return A;
  vector<Point> ans(2 * n);
  sort(A.begin(), A.end());
  for (int i = 0; i < n; ++i) {
    while (k >= 2 && cross_product(ans[k - 2], ans[k - 1], A[i]) < 0) k--;
    ans[k++] = A[i];
  }
  for (int i = n - 1, t = k + 1; i > 0; --i) {
    while (k >= t && cross_product(ans[k - 2], ans[k - 1], A[i - 1]) < 0) k--;
    ans[k++] = A[i - 1];
  }
  ans.resize(k - 1);
  return ans;
}

ld find_triangle_area(const vector<Point>& polygon, const int i) {
  ld ans = 0;
  ld curr = -1;

  for (int j = i + 1, k = i + 2; k < (int)polygon.size(); k++) {
    curr = -1;
    for (; j < k; j++) {
      ld area = triangle_area(polygon[i], polygon[j], polygon[k]);
      ans = max(ans, area);

      if (area <= curr || j == k - 1) {
        j--;
        break;
      }

      curr = area;
    }
  }

  return ans;
}

int main() {
  int N;
  cin >> N;

  vector<Point> points(N);

  for (int i = 0; i < N; i++) {
    cin >> points[i].x >> points[i].y;
  }

  vector<Point> hull = convex_hull(points);

  ld area = 0;

  for (int i = 0; i < (int)hull.size(); i++) {
    area = max(area, find_triangle_area(hull, i));
  }

  cout << fixed << setprecision(5) << area << endl;
}
