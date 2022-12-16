#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  ll cross(const Point& p) const { return x * p.y - y * p.x; }
  Point to(const Point& p) const { return p - *this; }
  Point rot_ccw() { return {-y, x}; }
  bool operator<(const Point& p) const { return y < p.y || (y == p.y && x < p.x); }
};

int N, K;
vector<Point> polygon, hull;

short sgn(const ll x) { return (x > 0) - (x < 0); }

short orientation(const Point& p, const Point& q, const Point& u, const Point& v) {
  return sgn(p.to(q).cross(u.to(v)));
}

short orientation(const Point& o, const Point& a, const Point& b) {
  return sgn(o.to(a).cross(o.to(b)));
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
  res.resize(k - 1);
  return res;
}

void to_ccw(vector<Point>& polygon) {
  if (polygon.size() < 3) return;
  if (orientation(polygon[0], polygon[1], polygon[2]) == -1) {
    reverse(polygon.begin(), polygon.end());
  }
}

vector<int> calculate_next_vertex() {
  vector<int> res;

  int i = 0;
  int j = 0;

  bool negative_found = false;

  for (int it = 0; it < 2 * K; it++, j++) {
    const Point p = polygon[0];
    const Point q = polygon[1];
    const Point u = hull[j % K];
    const Point v = hull[(j + 1) % K];

    if (negative_found && orientation(p, q, u, v) >= 0) {
      break;
    } else if (orientation(p, q, u, v) < 0) {
      negative_found = true;
    }
  }

  while ((int)res.size() < N) {
    const Point u = hull[j % K];
    const Point v = hull[(j + 1) % K];

    for (;; i++) {
      const Point p = polygon[res.size()];
      const Point q = polygon[(i + 2) % N];

      if (orientation(p, q, u, v) < 0) {
        j++;
        break;
      }

      if (orientation(p, q, u) <= 0) {
        res.push_back((i + 1) % N);
        break;
      }
    }
  }

  return res;
}

int count(const int i, const vector<vector<int>>& st) {
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
  srand(time(NULL));

  while (cin >> N) {
    polygon.resize(N);
    for (auto& p : polygon) cin >> p.x >> p.y;
    to_ccw(polygon);
    cin >> K;
    hull.resize(K);
    for (auto& p : hull) cin >> p.x >> p.y;
    hull = convex_hull(hull);
    K = hull.size();

    // Test data is very weak, so "randomize" it a bit in order to make sure my
    // program still works with slightly modified (but equivalent) data.
    const int rotations = rand() % 4;
    for (int r = 0; r < rotations; r++) {
      for (auto& p : polygon) p = p.rot_ccw();
      for (auto& p : hull) p = p.rot_ccw();
    }

    const auto shift = [](vector<Point>& P, const int n) {
      P.insert(P.end(), P.begin(), P.begin() + n);
      P.erase(P.begin(), P.begin() + n);
    };

    shift(polygon, rand() % polygon.size());
    shift(hull, rand() % hull.size());
    assert((int)polygon.size() == N);
    assert((int)hull.size() == K);

    vector<vector<int>> sparse_table(ceil(log2(N)) + 1);
    sparse_table[0] = calculate_next_vertex();

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
