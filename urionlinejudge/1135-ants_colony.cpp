#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef pair<int, ull> pil;
typedef vector<int> vi;
typedef vector<vector<pil>> graph;

struct LCA {
  const int root, n, log2_n;
  vector<vi> parent;
  vi depth;

  LCA(const graph& graph, int root, int n)
      : root(root), n(n), log2_n(log2(n) + 1), parent(log2_n, vi(n)), depth(n) {
    dfs(graph, root, root, 1);
    for (int k = 0; k + 1 < log2_n; ++k) {
      parent.push_back(vi(n, root));
      for (int v = n - 1; v >= 0; --v) {
        int par = parent[k][v];
        parent[k + 1][v] = parent[k][par];
      }
    }
  }

  void dfs(const graph& graph, int from, int par, int d) {
    parent[0][from] = par;
    depth[from] = d;
    for (pil to : graph[from]) {
      if (depth[to.first] > 0) continue;
      dfs(graph, to.first, from, d + 1);
    }
  }

  int operator()(int v1, int v2) {
    if (depth[v1] < depth[v2]) swap(v1, v2);
    for (int k = 0; k < log2_n; ++k)
      if ((depth[v1] - depth[v2]) >> k & 1) v1 = parent[k][v1];
    if (v1 == v2) return v1;
    for (int k = log2_n - 1; k >= 0; --k) {
      int p_v1 = parent[k][v1];
      int p_v2 = parent[k][v2];
      if (p_v1 == p_v2) continue;
      v1 = p_v1;
      v2 = p_v2;
    }
    return parent[0][v1];
  }
};

int n;
ull dist[100001];
bool visited[100001];

ull path_length(LCA& lca, int source, int target) {
  int ancestor_idx = lca(source, target);
  return dist[source] + dist[target] - (2 * dist[ancestor_idx]);
}

void populate_dist(graph& g, int idx, ull accum) {
  if (visited[idx]) return;
  visited[idx] = true;
  dist[idx] = accum;
  for (pil adj : g[idx]) populate_dist(g, adj.first, accum + adj.second);
}

void solve() {
  int v, w, q, s, t;
  memset(visited, 0, sizeof visited);
  graph g(n, vector<pil>());

  for (int i = 1; i < n; i++) {
    scanf("%d %d", &v, &w);
    g[i].push_back(make_pair(v, w));
    g[v].push_back(make_pair(i, w));
  }

  LCA lca(g, 0, n);

  populate_dist(g, 0, 0);

  scanf("%d", &q);
  while (q--) {
    scanf("%d %d", &s, &t);
    printf("%lld%c", path_length(lca, s, t), q > 0 ? ' ' : '\n');
  }
}

int main() {
  while (scanf("%d", &n) == 1 && n != 0) solve();
}
