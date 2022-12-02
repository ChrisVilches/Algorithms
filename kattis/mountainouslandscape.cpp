#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  int x, y;
  ll cross(const Point& p) const { return (ll)x * p.y - (ll)y * p.x; }
  inline Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline Point to(const Point& p) const { return p - *this; }
} points[100'007];

vector<Point> tree[4 * 100'007];
int idx[4 * 100'007];

short orientation(const Point o, const Point a, const Point b) {
  const ll cross = (a - o).cross(b - o);
  return cross < 0 ? -1 : (cross > 0);
}

void build(const int v, const int l, const int r) {
  vector<Point>& hull = tree[v];
  hull.resize(r - l + 1);
  int k = 0;

  for (int i = l; i <= r; i++) {
    while (k > 1 && orientation(hull[k - 2], hull[k - 1], points[i]) == 1) k--;
    hull[k++] = points[i];
  }

  hull.resize(k);

  if (l == r) {
    idx[v] = l;
  } else {
    build(2 * v, l, (l + r) / 2);
    build(2 * v + 1, 1 + (l + r) / 2, r);
  }
}

bool valid_node(const Point p, const Point q, const vector<Point>& hull) {
  if (hull.back().x <= q.x) return false;

  int lo = 0;
  int hi = hull.size() - 2;

  while (lo <= hi) {
    const int mid = (lo + hi) / 2;

    const Point p1 = hull[mid];
    const Point p2 = hull[mid + 1];

    if (p.to(q).cross(p1.to(p2)) < 0) {
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  return orientation(p, q, hull[lo]) == 1;
}

int query(const int v, const Point p, const Point q) {
  if (!valid_node(p, q, tree[v])) return 0;
  if (tree[v].size() == 1) return idx[v];

  const int idx = query(2 * v, p, q);
  if (idx != 0) return idx;
  return query(2 * v + 1, p, q);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T, N;
  cin >> T;

  while (T--) {
    cin >> N;

    for (int i = 0; i < N; i++) {
      cin >> points[i].x >> points[i].y;
    }

    build(1, 0, N - 1);

    for (int i = 0; i < N - 1; i++) {
      const Point p = points[i];
      const Point q = points[i + 1];
      cout << query(1, p, q) << ' ';
    }

    cout << endl;
  }
}
