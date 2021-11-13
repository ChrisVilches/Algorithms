#include <bits/stdc++.h>

using namespace std;

struct Point {
  double x, y, z;
  Point(double x, double y, double z) : x(x), y(y), z(z) {}
  Point() {}
  Point operator+(const Point& p) { return Point(x + p.x, y + p.y, z + p.z); }
  Point operator-(const Point& p) { return Point(x - p.x, y - p.y, z - p.z); }
  bool operator<(Point p) {
    if (y == p.y) return x < p.x;
    return y < p.y;
  }

  Point scale(double factor) {
    return Point(x * factor, y * factor, z * factor);
  }
};

int N;

double cross(Point& O, Point& A, Point& B) {
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

long double convex_hull_area(vector<Point> pts) {
  vector<Point> hull = convex_hull(pts);
  long double total = 0;
  for (int i = 2; i < (int)hull.size(); i++)
    total += fabs(cross(hull[0], hull[i - 1], hull[i])) / 2L;
  return total;
}

Point intersection_soil(Point alien, Point platform) {
  double left = 0;
  double right = 100000;
  int iters = 500;

  Point laser = platform - alien;
  Point ret;

  while (iters--) {
    double mid = (left + right) / 2.0;

    ret = laser.scale(mid) + alien;

    if (ret.z > 0)
      left = mid;
    else
      right = mid;
  }

  return ret;
}

void solve() {
  Point alien;
  vector<Point> platforms;

  cin >> alien.x >> alien.y >> alien.z;

  for (int i = 0; i < N; i++) {
    Point p;
    cin >> p.x >> p.y >> p.z;
    platforms.push_back(p);
  }

  vector<Point> soil;

  for (Point p : platforms) soil.push_back(intersection_soil(alien, p));

  printf("%.2Lf\n", convex_hull_area(soil));
}

int main() {
  while (scanf("%d", &N) == 1 && N > 0) solve();
}
