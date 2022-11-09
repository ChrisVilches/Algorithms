#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline ll cross(const Point& p) const { return x * p.y - y * p.x; }
  Point to(const Point& p) const { return p - *this; }
};

struct Segment {
  Point p, q;

  bool below(const Segment& s) const {
    if (!x_overlap(s)) return false;

    if (vertical() && !s.vertical()) {
      return s.to_vec().cross(s.p.to(p)) < 0;
    }

    if (p.x <= s.p.x) {
      return to_vec().cross(p.to(s.p)) > 0;
    } else {
      return s.to_vec().cross(s.p.to(p)) < 0;
    }
  }

 private:
  Point to_vec() const { return p.to(q); }

  bool vertical() const { return p.x == q.x; }

  bool contains_x(const Point& r) const { return p.x <= r.x && r.x <= q.x; }

  bool x_overlap(const Segment& s) const {
    return contains_x(s.p) || contains_x(s.q) || s.contains_x(p) || s.contains_x(q);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N;

  while (cin >> N) {
    vector<Segment> segments(N);

    for (auto& s : segments) {
      cin >> s.p.x >> s.p.y >> s.q.x >> s.q.y;
      if (s.p.x > s.q.x) swap(s.p, s.q);
    }

    vector<vector<int>> tree(N);

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (i == j) continue;

        if (segments[i].below(segments[j])) {
          tree[j].push_back(i);
        }
      }
    }

    vector<bool> visited(N, false);

    const function<void(int)> dfs = [&](const int u) -> void {
      if (visited[u]) return;
      visited[u] = true;

      for (const int v : tree[u]) {
        dfs(v);
      }
      cout << u + 1 << ' ';
    };

    for (int i = 0; i < N; i++) {
      dfs(i);
    }

    cout << endl;
  }
}
