#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
  int x, y;
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  ll cross(const Point p) const { return (ll)x * p.y - (ll)y * p.x; }
  bool operator<(const Point p) const { return to_upper().cross(p.to_upper()) > 0; }
  Point to_upper() const { return y > 0 || (y == 0 && x > 0) ? *this : negate(); }
  ll operator*(const Point p) const { return (ll)x * p.x + (ll)y * p.y; }
  bool deg0(const Point p) const { return cross(p) == 0 && *this * p >= 0; }
  Point negate() const { return {-x, -y}; }
};

short orientation(const Point o, const Point a, const Point b) {
  const ll x = (a - o).cross(b - o);
  return (x > 0) - (x < 0);
}

vector<Point> convex_hull(vector<Point> A) {
  int n = A.size(), k = 0;
  if (n <= 2) return A;
  vector<Point> res(n + 1);
  sort(A.begin(), A.end(), [](const Point p, const Point q) {
    return p.y < q.y || (p.y == q.y && p.x < q.x);
  });
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

int find_tangent(const vector<Point>& polygon, const Point p, const bool left) {
  const int n = polygon.size();
  int lo = 0;
  int hi = n;
  const bool dir = orientation(p, polygon[0], polygon[1]) == -1;

  while (lo <= hi) {
    const int mid = (lo + hi) / 2;
    const Point curr = polygon[mid % n];
    const Point prev = polygon[(mid - 1 + n) % n];
    const Point next = polygon[(mid + 1) % n];

    const short side = left ? -1 : 1;
    const short or1 = orientation(p, curr, prev);
    const short or2 = orientation(p, curr, next);
    if ((or1 == 0 || or1 == side) && (or2 == 0 || or2 == side)) return mid % n;

    const bool invalid = orientation(p, polygon[0], curr) == side;

    if ((!invalid && orientation(p, curr, next) == -side) || (invalid && left == dir)) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }

  assert(false);
}

bool inside_triangle(const Point a, const Point b, const Point c, const Point p) {
  return orientation(a, b, p) >= 0 && orientation(b, c, p) >= 0 &&
         orientation(c, a, p) >= 0;
}

bool inside_segment(const Point p, const Point q, const Point r) {
  return (q - p).deg0(r - p) && (p - q).deg0(r - q);
}

bool inside(const vector<Point>& polygon, const Point p) {
  if (polygon.size() <= 2) return inside_segment(polygon.front(), polygon.back(), p);

  const auto cmp = [&](const Point p, const Point q) {
    return orientation(polygon[0], p, q) == -1;
  };

  const auto it = lower_bound(polygon.rbegin() + 1, polygon.rend() - 1, p, cmp);
  return inside_triangle(polygon[0], *it, *prev(it), p);
}

int sweep_max(const vector<tuple<Point, bool, int>>& events) {
  int result = 0;

  unordered_set<int> active;

  for (int it = 0; it < 2; it++) {
    for (const auto& [_, enter, idx] : events) {
      if (enter) {
        active.emplace(idx);
      } else {
        active.erase(idx);
      }

      result = max(result, (int)active.size());
    }
  }

  return result;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N;

  while (cin >> N) {
    array<vector<Point>, 2> points;
    for (int i = 0; i < N; i++) {
      Point p;
      int label;
      cin >> p.x >> p.y >> label;
      points[label].push_back(p);
    }

    const vector<Point> polygon = convex_hull(points[1]);

    if (polygon.size() == 1) {
      cout << 1 << endl;
      continue;
    }

    vector<tuple<Point, bool, int>> events;

    for (int i = 0; i < (int)points[0].size(); i++) {
      const Point p = points[0][i];
      if (inside(polygon, p)) continue;

      const int idx1 = find_tangent(polygon, p, true);
      const int idx2 = find_tangent(polygon, p, false);

      events.emplace_back(polygon[idx2] - p, false, i);
      events.emplace_back(p - polygon[idx1], true, i);
    }

    sort(events.begin(), events.end());

    cout << N - sweep_max(events) << endl;
  }
}
