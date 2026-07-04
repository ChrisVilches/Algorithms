#include <bits/stdc++.h>
using namespace std;

struct BIT {
  BIT(const int size) : n(size + 1), A(n, 0) {}

  void range_update(const int i, const int j, const int v) {
    update(i, v);
    update(j + 1, -v);
  }

  int query(int i) const {
    i++;
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

 private:
  const int n;
  vector<int> A;
  void update(int i, const int v) {
    i++;
    for (; i < n; i += i & -i) A[i] += v;
  }
};

struct Point {
  long long x, y;
  bool operator<(const Point p) const { return x < p.x; }
  long long cross(const Point p) const { return x * p.y - y * p.x; }
};

int main() {
  int n;
  while (cin >> n) {
    vector<tuple<int, int, int, int>> events;

    for (int k = 0; k < n; k++) {
      int m;
      cin >> m;
      vector<Point> polygon(m);

      for (Point& p : polygon) cin >> p.x >> p.y;

      long long area2 = 0;
      for (int i = m - 1, j = 0; j < m; i = j++) {
        area2 += polygon[i].cross(polygon[j]);
      }

      if (area2 < 0) {
        reverse(polygon.begin(), polygon.end());
      }

      for (int i = m - 1, j = 0; j < m; i = j++) {
        const Point p = polygon[i];
        const Point q = polygon[j];
        if (p.x == q.x) {
          const int y0 = min(p.y, q.y);
          const int y1 = max(p.y, q.y);
          const int delta = p.y < q.y ? -1 : 1;
          events.emplace_back(p.x * 2, y0 * 2, y1 * 2, delta);
        }
      }
    }

    int q;
    cin >> q;
    vector<pair<Point, int>> queries;

    for (int i = 0; i < q; i++) {
      Point p;
      cin >> p.x >> p.y;
      p.x = (p.x * 2) + 1;
      p.y = (p.y * 2) + 1;
      queries.emplace_back(p, i);
    }

    sort(queries.begin(), queries.end());
    sort(events.begin(), events.end());

    const int max_n = 2 * 100'000 + 7;
    BIT bit(max_n);

    int i = 0;
    vector<int> ans(q, 0);

    for (const auto& [x, y0, y1, delta] : events) {
      while (i < q && queries[i].first.x < x) {
        ans[queries[i].second] = bit.query(queries[i].first.y);
        i++;
      }

      bit.range_update(y0, y1, delta);
    }

    for (const int a : ans) {
      cout << a << endl;
    }
  }
}
