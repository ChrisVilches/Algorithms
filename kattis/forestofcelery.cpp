#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  long long cross(const Point p) const { return (long long)x * p.y - (long long)y * p.x; }
  bool operator<(const Point p) const { return y < p.y || (y == p.y && x < p.x); }
};

short orientation(const Point o, const Point a, const Point b) {
  const long long x = (a - o).cross(b - o);
  return (x > 0) - (x < 0);
}

vector<Point> convex_hull(vector<Point> A) {
  int n = A.size(), k = 0;
  if (n <= 2) return A;
  vector<Point> res(n + 1);
  sort(A.begin(), A.end());
  for (int i = 0; i < n; i++) {
    while (k >= 2 && orientation(res[k - 2], res[k - 1], A[i]) <= 0) k--;
    res[k++] = A[i];
  }
  for (int i = n - 1, t = k + 1; i > 0; i--) {
    while (k >= t && orientation(res[k - 2], res[k - 1], A[i - 1]) <= 0) k--;
    res[k++] = A[i - 1];
  }
  return {res.begin(), res.begin() + k - 1};
}

vector<int> find_next_vertex(const vector<Point>& polygon, const vector<Point>& hull) {
  const int N = polygon.size();
  const int M = hull.size();
  vector<int> res(N);

  for (int i = 0, j = 0, k = 1; i < N; i++) {
    const Point p = polygon[i];
    while (orientation(p, hull[j % M], hull[(j - 1 + M) % M]) == -1 ||
           orientation(p, hull[j % M], hull[(j + 1) % M]) == -1)
      j++;

    while (orientation(p, polygon[(k + 1) % N], hull[j % M]) > 0) k++;

    res[i] = k % N;
  }

  return res;
}

int count(const int i, const vector<vector<int>>& st) {
  const int N = st.front().size();
  int prev_idx = i;
  int res = 0;
  int col = i;

  for (bool done = false; !done;) {
    for (int k = 0; k < (int)st.size(); k++) {
      int curr = st[k][col];
      while (curr <= prev_idx) curr += N;
      if (i + N <= curr) {
        if (k == 0) {
          res++;
          done = true;
        } else {
          col = st[k - 1][col];
          res += 1 << (k - 1);
        }
        break;
      }

      prev_idx = curr;
    }
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N, K;

  while (cin >> N) {
    vector<Point> polygon(N);
    for (auto& p : polygon) cin >> p.x >> p.y;

    if (orientation(polygon[0], polygon[1], polygon[2]) == -1) {
      reverse(polygon.begin(), polygon.end());
    }

    cin >> K;
    vector<Point> points(K);
    for (auto& p : points) cin >> p.x >> p.y;

    vector<vector<int>> sparse_table(ceil(log2(N)) + 1);
    sparse_table[0] = find_next_vertex(polygon, convex_hull(points));

    for (int k = 1; k < (int)sparse_table.size(); k++) {
      for (int i = 0; i < N; i++) {
        sparse_table[k].push_back(sparse_table[k - 1][sparse_table[k - 1][i]]);
      }
    }

    int ans = INT_MAX;

    for (int i = 0; i < N; i++) {
      ans = min(ans, count(i, sparse_table));
    }

    cout << ans << endl;
  }
}
