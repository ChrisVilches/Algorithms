#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Point {
  int x, y;
  Point() {}
  Point(int x, int y) : x(x), y(y) {}

  inline bool operator<(const Point& p) const {
    if (y == p.y) return x < p.x;
    return y < p.y;
  }
};

ll cross_product(Point& O, Point& A, Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Convex hull (includes collinear points).
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

set<Point> convex_hull_set(vector<Point>& pts) {
  vector<Point> hull = convex_hull(pts);
  return set<Point>(hull.begin(), hull.end());
}

bool solve(int N) {
  vector<Point> pts;

  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    pts.push_back(Point(x, y));
  }

  int layers = 0;

  while (pts.size() >= 3) {
    set<Point> hull = convex_hull_set(pts);
    vector<Point> new_onion;

    for (Point& p : pts)
      if (!hull.count(p)) new_onion.push_back(p);

    pts = new_onion;
    layers++;
  }

  return layers % 2 == 1;
}

int main() {
  int N;

  while (scanf("%d", &N) == 1 && N != 0) {
    if (solve(N)) {
      cout << "Take this onion to the lab!" << endl;
    } else {
      cout << "Do not take this onion to the lab!" << endl;
    }
  }
}
