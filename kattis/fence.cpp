#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y, v, length;
  bool operator<(const Point p) const {
    if (y == p.y) return x < p.x;
    return y < p.y;
  }
  double dist(const Point p) const { return hypot(x - p.x, y - p.y); }
};

int cross_product(Point& O, Point& A, Point& B) {
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

void solve(const int N) {
  vector<Point> points(N);
  for (auto& p : points) cin >> p.x >> p.y >> p.v >> p.length;

  int min_lost_value = INT_MAX;

  for (int subset = 0; subset < (1 << N); subset++) {
    int lost_value = 0;
    double available_wood = 0;

    vector<Point> remaining_points;

    for (int i = 0; i < N; i++) {
      if ((subset & (1 << i)) != 0) {
        remaining_points.push_back(points[i]);
      } else {
        lost_value += points[i].v;
        available_wood += points[i].length;
      }
    }

    const vector<Point> hull = convex_hull(remaining_points);
    double total_length = 0;

    for (int i = 0; i < (int)hull.size(); i++) {
      total_length += hull[i].dist(hull[(i + 1) % hull.size()]);
    }

    if (total_length <= available_wood) {
      min_lost_value = min(min_lost_value, lost_value);
    }
  }

  cout << "The lost value is " << min_lost_value << "." << endl;
}

int main() {
  int N;
  while (cin >> N && N) solve(N);
}
