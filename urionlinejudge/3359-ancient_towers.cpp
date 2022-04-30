#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <class T>
struct BIT {
  BIT(const int n) : n(n) { bit.assign(n, 0); }

  void clear(const int n) { fill(bit.begin(), bit.begin() + n, 0); }

  T sum(int l, int r) { return sum(r) - sum(l - 1); }

  void add(int idx, const T delta) {
    for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;
  }

 private:
  vector<T> bit;
  int n;

  T sum(int r) {
    T ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
    return ret;
  }
};

struct Point {
  ll x, y;
  int id;

  inline Point operator-(const Point& p) const { return {x - p.x, y - p.y, id}; }
  inline ll cross(const Point& p) const { return x * p.y - y * p.x; }
  inline bool is_above() const { return y > 0 || (y == 0 && x > 0); }
  inline bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
} points[401];

int N, idx_map[401];
ll S, total, concave_count;
BIT<ll> active(401);

void count_all(const vector<Point>& points, int center_idx) {
  const int n = points.size();

  for (int i = 0; i < n; i++) {
    const Point diagonal = points[i];

    vector<pair<ll, int>> areas;

    for (const Point& p : points) {
      const ll area = diagonal.cross(p);

      if (area < 0) areas.push_back({-area, p.id});
    }

    if (areas.empty()) continue;

    const int first_i = (i + 1) % n;
    if (diagonal.cross(points[first_i]) < 0) continue;

    Point p1, p2;

    sort(areas.begin(), areas.end());

    for (int area_idx = 0; area_idx < (int)areas.size(); area_idx++) {
      const auto [_, point_id] = areas[area_idx];
      idx_map[point_id] = area_idx;
    }

    int k = first_i;

    for (;; k = (k + 1) % n) {
      p2 = points[k];
      if (diagonal.cross(p2) < 0) break;
    }

    active.clear(areas.size());

    for (int j = first_i;; j++) {
      p1 = points[j % n];
      if (diagonal.cross(p1) < 0) break;

      while (diagonal.cross(p2) < 0) {
        if (p1.cross(p2) < 0) break;

        active.add(idx_map[p2.id], 1);
        k = (k + 1) % n;
        p2 = points[k];
      }

      const ll complement = S * 2L - diagonal.cross(p1);

      if (center_idx < diagonal.id) {
        total += areas.end() -
                 lower_bound(areas.begin(), areas.end(), make_pair(complement, -1));
      }

      const int idx = lower_bound(areas.begin(), areas.end(), make_pair(complement, -1)) -
                      areas.begin();

      concave_count += active.sum(idx, areas.size() - 1);
    }
  }
}

void solve() {
  for (int i = 0; i < N; i++) {
    cin >> points[i].x >> points[i].y;
    points[i].id = i;
  }

  total = 0;
  concave_count = 0;

  for (int i = 0; i < N; i++) {
    vector<Point> centered_points;

    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      centered_points.push_back(points[j] - points[i]);
    }

    sort(centered_points.begin(), centered_points.end());

    count_all(centered_points, i);
  }

  const ll convex_polygons = (total - concave_count) / 2L;

  cout << total - convex_polygons << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> S >> N) solve();
}
