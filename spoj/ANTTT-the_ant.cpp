#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;

  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
  Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  ll cross(const Point& p) const { return (x * p.y) - (y * p.x); }
  Point to(const Point& p) const { return p - *this; }
};

struct Segment {
  Point p, q;

  int orientation(const Point& p, const Point& q, const Point& r) const {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
  }

  bool touch(const Segment& s) const {
    return p == s.p || p == s.q || q == s.p || q == s.q;
  }

  bool intersect(const Segment& s) const {
    if (touch(s)) return true;

    const Point p1 = p;
    const Point q1 = q;
    const Point p2 = s.p;
    const Point q2 = s.q;
    const int o1 = orientation(p1, q1, p2);
    const int o2 = orientation(p1, q1, q2);
    const int o3 = orientation(p2, q2, p1);
    const int o4 = orientation(p2, q2, q1);
    return (o1 != o2 && o3 != o4);
  }
};

struct DisjointSets {
  DisjointSets(int n) : parent(n), rank(n, 0) { iota(parent.begin(), parent.end(), 0); }

  int find(int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) {
    x = find(x), y = find(y);
    if (rank[x] > rank[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rank[x] == rank[y]) rank[y]++;
  }

 private:
  vector<int> parent, rank;
};

void solve() {
  int N, Q;
  cin >> N >> Q;

  vector<vector<int>> graph(N);

  vector<Segment> segments(N);

  for (int i = 0; i < N; i++) {
    cin >> segments[i].p.x >> segments[i].p.y;
    cin >> segments[i].q.x >> segments[i].q.y;
  }

  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      if (segments[i].intersect(segments[j])) {
        graph[i].push_back(j);
        graph[j].push_back(i);
      }
    }
  }

  vector<bool> visited(N, false);

  DisjointSets ds(N);

  function<void(int)> dfs = [&](const int u) {
    visited[u] = true;

    for (const int v : graph[u]) {
      if (visited[v]) continue;
      ds.merge(u, v);
      dfs(v);
    }
  };

  for (int i = 0; i < N; i++) {
    if (visited[i]) continue;
    dfs(i);
  }

  while (Q--) {
    int u, v;
    cin >> u >> v;

    cout << (ds.find(u - 1) == ds.find(v - 1) ? "YES" : "NO") << endl;
  }
}

int main() {
  int t;
  cin >> t;

  while (t--) solve();
}
