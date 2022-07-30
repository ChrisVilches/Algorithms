#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef bitset<2501> mst_t;

struct Point {
  double x, y, z;
  Point operator+(const Point& p) const { return {x + p.x, y + p.y, z + p.z}; }
  Point scale(const double f) const { return {x * f, y * f, z * f}; }
  double dist(const Point& p) const { return hypot(x - p.x, y - p.y, z - p.z); }
};

struct DisjointSets {
  DisjointSets(int n) : parent(n), rank(n, 0) { iota(parent.begin(), parent.end(), 0); }

  int find(const int u) {
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

struct Graph {
  Graph(int V) : V(V) {}

  void add_edge(const int u, const int v, const double w) {
    edges.push_back({w, {u, v}});
  }

  mst_t kruskal_mst() {
    sort(edges.begin(), edges.end());

    DisjointSets ds(V);

    mst_t res;

    for (const auto& [_, edge] : edges) {
      const auto [u, v] = edge;
      const int set_u = ds.find(u);
      const int set_v = ds.find(v);

      if (set_u == set_v) continue;

      res.set(u * 50 + v);
      ds.merge(set_u, set_v);
    }

    return res;
  }

 private:
  const int V;
  vector<pair<double, pii>> edges;
};

vector<Point> points;
vector<Point> vel;

mst_t calculate_mst(const double t) {
  const int N = points.size();
  vector<Point> new_points = points;

  for (int i = 0; i < N; i++) new_points[i] = new_points[i] + vel[i].scale(t);

  Graph g(N);

  for (int i = 0; i < N; i++)
    for (int j = i + 1; j < N; j++) g.add_edge(i, j, new_points[i].dist(new_points[j]));

  return g.kruskal_mst();
}

int main() {
  int N;
  int test_case = 1;

  while (cin >> N) {
    points.resize(N);
    vel.resize(N);

    for (int i = 0; i < N; i++) {
      Point& p = points[i];
      Point& v = vel[i];

      cin >> p.x >> p.y >> p.z;
      cin >> v.x >> v.y >> v.z;
    }

    double t = 0;
    const double t_max = 1000000;

    int ans = 0;

    for (; t < t_max; ans++) {
      const mst_t initial = calculate_mst(t + 1e-5);

      double lo = t;
      double hi = t_max;

      for (int it = 0; it < 100; it++) {
        const double mid = (lo + hi) / 2;

        const mst_t mst = calculate_mst(mid);

        if (initial == mst) {
          lo = mid;
        } else {
          hi = mid;
        }
      }

      t = lo;
    }

    cout << "Case " << test_case++ << ": " << ans << endl;
  }
}
