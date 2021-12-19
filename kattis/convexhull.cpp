#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  int x, y;
  bool operator<(const Point& p) const {
    if (y == p.y) return x < p.x;
    return y < p.y;
  }
};

ll cross_product(Point& O, Point& A, Point& B) {
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
  for (size_t i = n - 1, t = k + 1; i > 0; --i) {
    while (k >= t && cross_product(ans[k - 2], ans[k - 1], A[i - 1]) <= 0) k--;
    ans[k++] = A[i - 1];
  }
  ans.resize(k - 1);
  return ans;
}

int N;

void solve() {
  vector<Point> points(N);
  for (int i = 0; i < N; i++) cin >> points[i].x >> points[i].y;

  vector<Point> hull = convex_hull(points);

  set<pair<int, int>> repeated;
  int size = 0;

  for (const Point& p : hull) {
    if (repeated.count({p.x, p.y})) continue;
    size++;
    repeated.insert({p.x, p.y});
  }

  repeated.clear();
  cout << size << endl;

  for (const Point& p : hull) {
    if (repeated.count({p.x, p.y})) continue;
    cout << p.x << ' ' << p.y << endl;
    repeated.insert({p.x, p.y});
  }
}

int main() {
  while (scanf("%d", &N) == 1 && N) solve();
}
