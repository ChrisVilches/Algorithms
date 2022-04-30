#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: Use my own
struct FenwickTree {
  vector<int> bit;
  int n;

  FenwickTree(int n) {
    this->n = n;
    bit.assign(n, 0);
  }

  void clear(const int n) { fill(bit.begin(), bit.begin() + n, 0); }

  int sum(int r) {
    int ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
    return ret;
  }

  int sum(int l, int r) { return sum(r) - sum(l - 1); }

  void add(int idx, int delta) {
    for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;
  }
};

struct Point {
  ll x, y;
  int id;

  static Point from_stdin(const int id) {
    Point p;
    cin >> p.x >> p.y;
    p.id = id;
    return p;
  }
  inline Point to(const Point& p) const { return p - *this; }
  inline Point operator-(const Point& p) const { return {x - p.x, y - p.y, id}; }
  inline ll cross(const Point& p) const { return x * p.y - y * p.x; }
  inline bool is_above() const { return y > 0 || (y == 0 && x > 0); }
  inline bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
} points[401];

int N;
ll S, total, concave_counts[401][401];
int id_idx[401];

ll cross(const Point& a, const Point& b, const Point& c) {
  return a.to(b).cross(a.to(c));
}

FenwickTree active(401);

void count_all(const vector<Point>& points, int center_idx) {
  const int n = points.size();

  for (int i = 0; i < n; i++) {
    const Point diagonal = points[i];

    concave_counts[center_idx][diagonal.id] = 0;

    vector<pair<ll, int>> areas;

    for (const Point& p : points) {
      const ll area = diagonal.cross(p);

      if (area < 0) areas.push_back({-area, p.id});
    }

    if (areas.empty()) continue;

    int real_i = (i + 1) % n;

    if (diagonal.cross(points[real_i]) < 0) continue;

    int k = real_i;

    Point p2;

    sort(areas.begin(), areas.end());

    for (int x = 0; x < (int)areas.size(); x++) {
      const auto [_, id] = areas[x];
      id_idx[id] = x;
    }

    // TODO: Can probably be optimized by keeping the iterator K in the same place,
    //       and then finding the next position based on the previous iteration (requires
    //       less iterations)
    for (;; k++) {
      k %= (int)points.size();
      p2 = points.at(k);
      if (diagonal.cross(p2) < 0) break;
    }

    p2 = points.at(k);

    active.clear(areas.size());

    for (int j = real_i;; j++) {
      const Point p1 = points[j % (int)points.size()];
      if (diagonal.cross(p1) < 0) break;

      const ll curr_area = diagonal.cross(p1);

      while (diagonal.cross(p2) < 0) {
        if (p1.cross(p2) > 0) {
          const int idx = id_idx[p2.id];
          active.add(idx, 1);
          k++;
          p2 = points.at(k % (int)points.size());
        } else {
          break;
        }
      }

      const ll complement = S * 2L - curr_area;

      if (center_idx < diagonal.id) {
        total += areas.end() -
                 lower_bound(areas.begin(), areas.end(), make_pair(complement, -1));
      }

      const int idx = lower_bound(areas.begin(), areas.end(), make_pair(complement, -1)) -
                      areas.begin();

      concave_counts[center_idx][diagonal.id] += active.sum(idx, areas.size() - 1);
    }
  }
}

void solve() {
  for (int i = 0; i < N; i++) points[i] = Point::from_stdin(i);

  total = 0;

  for (int i = 0; i < N; i++) {
    vector<Point> centered_points;

    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      centered_points.push_back(points[i].to(points[j]));
    }

    sort(centered_points.begin(), centered_points.end());

    count_all(centered_points, i);
  }

  ll ans = total;

  ll convex_polygons = total;

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) convex_polygons -= concave_counts[i][j];

  convex_polygons /= 2L;
  ans -= convex_polygons;

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> S >> N) solve();
}
