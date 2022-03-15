#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
struct Point;
typedef pair<Point, Point> pp;

#define MAX 100001

struct LCA {
  const int root, n, log2_n;
  vector<vi> parent;
  vi depth;

  LCA(const vector<vi>& graph, int root)
      : root(root),
        n(graph.size()),
        log2_n(log2(n) + 1),
        parent(log2_n, vi(n)),
        depth(n) {
    dfs(graph, root, root, 1);
    for (int k = 0; k + 1 < log2_n; ++k) {
      parent.push_back(vi(n, root));
      for (int v = n - 1; v >= 0; --v) parent[k + 1][v] = parent[k][parent[k][v]];
    }
  }

  void dfs(const vector<vi>& graph, int u, int par, int d) {
    parent[0][u] = par;
    depth[u] = d;
    for (int v : graph[u])
      if (depth[v] == 0) dfs(graph, v, u, d + 1);
  }

  int operator()(int v1, int v2) const {
    if (depth[v1] < depth[v2]) swap(v1, v2);
    for (int k = 0; k < log2_n; ++k)
      if ((depth[v1] - depth[v2]) >> k & 1) v1 = parent[k][v1];
    if (v1 == v2) return v1;
    for (int k = log2_n - 1; k >= 0; --k) {
      int p_v1 = parent[k][v1], p_v2 = parent[k][v2];
      if (p_v1 != p_v2) v1 = p_v1, v2 = p_v2;
    }
    return parent[0][v1];
  }
};

struct Point {
  ll x, y;
  bool operator==(const Point& p) const { return x == p.x && y == p.y; }
  Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
  ll operator^(const Point& p) const { return x * p.y - y * p.x; }
  bool operator<(const Point& p) const { return y == p.y ? x < p.x : y < p.y; }
  Point to(const Point& p) const { return p - *this; }
  static Point from_stdin() {
    Point p;
    cin >> p.x >> p.y;
    return p;
  }
};

int N, Q, dist[MAX], global_triangle_idx = 0;
map<pp, vector<int>> diagonal_triangles;

pp make_normalized_pair(const Point& a, const Point& b) {
  return a < b ? make_pair(a, b) : make_pair(b, a);
}

struct Node {
  Node(const vector<Point>& polygon, const vector<pp>& diagonals) {
    if (polygon.size() == 3) {
      const Point &p = polygon[0], &q = polygon[1], &r = polygon[2];

      idx = global_triangle_idx++;
      diagonal_triangles[make_normalized_pair(p, q)].push_back(idx);
      diagonal_triangles[make_normalized_pair(q, r)].push_back(idx);
      diagonal_triangles[make_normalized_pair(r, p)].push_back(idx);
      return;
    }

    set_best_divider(polygon, diagonals);

    const auto [polygon1, polygon2] = divide_polygon(polygon);
    const auto [diag1, diag2] = divide_diagonals(diagonals);

    children = {make_unique<Node>(polygon1, diag1), make_unique<Node>(polygon2, diag2)};
  }

  int query_triangle_idx(const Point& p) const {
    if (children[0] == nullptr && children[1] == nullptr) return idx;

    const auto [u, v] = divider;
    int child_idx = (u.to(v) ^ u.to(p)) < 0 ? 0 : 1;
    return children[child_idx]->query_triangle_idx(p);
  }

 private:
  pp divider;
  int idx;
  array<unique_ptr<Node>, 2> children{nullptr, nullptr};

  void set_best_divider(const vector<Point>& polygon, const vector<pp>& diagonals) {
    int best_vertices_diff = INT_MAX;
    map<Point, int> point_to_index;

    for (int i = 0; i < (int)polygon.size(); i++) point_to_index[polygon[i]] = i;

    for (const auto& [u, v] : diagonals) {
      int side1 = abs(point_to_index[u] - point_to_index[v]);
      int side2 = polygon.size() - side1;
      int diff = abs(side1 - side2);

      if (diff < best_vertices_diff) {
        best_vertices_diff = diff;
        divider = {u, v};
      }
    }
  }

  array<vector<pp>, 2> divide_diagonals(const vector<pp>& diagonals) const {
    array<vector<pp>, 2> res;
    const auto [a, b] = divider;

    for (const auto& [u, v] : diagonals) {
      ll cross1 = a.to(b) ^ (a.to(u));
      ll cross2 = a.to(b) ^ (a.to(v));
      if (cross1 == 0 && cross2 == 0) continue;

      res[cross1 > 0 || cross2 > 0].push_back({u, v});
    }

    return res;
  }

  array<vector<Point>, 2> divide_polygon(const vector<Point>& polygon) const {
    vector<Point> polygon1, polygon2;
    int i = find(polygon.begin(), polygon.end(), divider.first) - polygon.begin();

    for (;; i = (i + 1) % polygon.size()) {
      polygon1.push_back(polygon[i]);
      if (polygon1.back() == divider.second) break;
    }

    for (;; i = (i + 1) % polygon.size()) {
      polygon2.push_back(polygon[i]);
      if (polygon2.back() == divider.first) break;
    }

    return {polygon1, polygon2};
  }
};

int path_length(const LCA& lca, int source, int target) {
  int ancestor_idx = lca(source, target);
  return dist[source] + dist[target] - 2 * dist[ancestor_idx];
}

void populate_dist(const vector<vi>& g, int u, int accum) {
  if (~dist[u]) return;
  dist[u] = accum;
  for (int v : g[u]) populate_dist(g, v, accum + 1);
}

pair<int, vector<vi>> make_graph() {
  vector<vi> graph(N - 2);

  auto add_edge = [&](int u, int v) -> void {
    graph[u].push_back(v);
    graph[v].push_back(u);
  };

  for (auto const& [_, triangles_idx] : diagonal_triangles)
    if (triangles_idx.size() == 2) add_edge(triangles_idx[0], triangles_idx[1]);

  return {0, graph};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N) {
    fill(dist, dist + N, -1);
    global_triangle_idx = 0;
    diagonal_triangles.clear();

    vector<Point> polygon(N);
    vector<pp> diagonals;

    for (int i = 0; i < N; i++) polygon[i] = Point::from_stdin();

    for (int i = 0; i < N - 3; i++) {
      int u, v;
      cin >> u >> v;
      diagonals.push_back({polygon[u - 1], polygon[v - 1]});
    }

    Node tree_root(polygon, diagonals);

    auto [root_idx, graph] = make_graph();
    populate_dist(graph, root_idx, 0);

    LCA lca(graph, root_idx);

    cin >> Q;

    while (Q--) {
      int node_idx1 = tree_root.query_triangle_idx(Point::from_stdin());
      int node_idx2 = tree_root.query_triangle_idx(Point::from_stdin());

      cout << path_length(lca, node_idx1, node_idx2) << '\n';
    }
  }
}
