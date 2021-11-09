#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  int x, y, id;
  bool operator<(Point p) {
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

double dist(Point& p1, Point& p2) {
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void solve() {
  int N;
  cin >> N;
  vector<Point> points;
  set<pair<int, int>> present;
  for (int i = 0; i < N; i++) {
    Point p;
    cin >> p.x >> p.y;
    if (present.find(make_pair(p.x, p.y)) != present.end()) continue;
    p.id = i + 1;
    points.push_back(p);
    present.emplace(make_pair(p.x, p.y));
  }

  vector<Point> hull = convex_hull(points);

  double total_dist = 0;
  for (int i = 0; i < (int)hull.size(); i++) {
    total_dist += dist(hull[i], hull[(i + 1) % N]);
  }

  printf("%.2f\n", total_dist);
  for (Point p : hull) {
    cout << p.id << " ";
  }
  cout << endl << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
