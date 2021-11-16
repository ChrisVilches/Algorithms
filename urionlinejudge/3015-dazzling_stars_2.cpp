#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  int brightness = 0;

  Point() {}
  Point(ll x, ll y) : x(x), y(y) {}

  inline Point operator-(const Point &p) const {
    return Point(x - p.x, y - p.y);
  }
  inline ll operator^(const Point &p) const { return x * p.y - y * p.x; }

  bool operator<(const Point &p) const {
    if (y == p.y) return x > p.x;
    return y > p.y;
  }
};

inline ll cross_product(Point &O, Point &A, Point &B) {
  return (A - O) ^ (B - A);
}

vector<Point> convex_hull(vector<Point> &A) {
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

int N;

bool possible() {
  vector<Point> points;

  while (N--) {
    Point p;
    cin >> p.x >> p.y >> p.brightness;
    points.push_back(p);
  }

  if (points.size() <= 3) return true;

  vector<Point> pts{Point(0, 0)};

  for (int i = 0; i < (int)points.size(); i++)
    for (int j = 0; j < (int)points.size(); j++) {
      if (i == j) continue;
      if (points[i].brightness < points[j].brightness)
        pts.push_back(points[j] - points[i]);
    }

  if (pts.size() <= 3) return true;

  vector<Point> hull = convex_hull(pts);

  for (int i = 0; i < (int)hull.size(); i++) {
    Point &p = hull[i];
    Point &q = hull[(i + 1) % hull.size()];
    if (((q - p) ^ (Point(0, 0) - p)) == 0) return true;
  }

  return false;
}

int main() {
  while (scanf("%d", &N) == 1) cout << (possible() ? 'Y' : 'N') << endl;
}
