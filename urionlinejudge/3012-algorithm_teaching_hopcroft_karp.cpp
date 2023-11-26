#include <bits/stdc++.h>
using namespace std;

hash<string> hasher;

class HopcroftKarp {
  vector<vector<int>> graph;
  vector<int> dist, match;
  vector<bool> used, visited;

  void bfs() {
    dist.assign(graph.size(), -1);
    queue<int> q;
    for (int i = 0; i < (int)graph.size(); i++)
      if (!used[i]) q.emplace(i), dist[i] = 0;

    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      for (const auto v : graph[u]) {
        const int m = match[v];
        if (m != -1 && dist[m] == -1) dist[m] = dist[u] + 1, q.emplace(m);
      }
    }
  }

  bool dfs(const int u) {
    visited[u] = true;
    for (const auto v : graph[u]) {
      const int m = match[v];
      if (m == -1 || (!visited[m] && dist[m] == dist[u] + 1 && dfs(m))) {
        match[v] = u, used[u] = true;
        return true;
      }
    }
    return false;
  }

 public:
  HopcroftKarp(const int n, const int m) : graph(n), match(m, -1), used(n), visited(n) {}

  void add_edge(const int u, const int v) { graph[u].push_back(v); }

  int max_bipartite_matching() {
    int flow, ret = 0;
    do {
      bfs();
      fill(visited.begin(), visited.end(), false);
      flow = 0;
      for (int i = 0; i < (int)graph.size(); i++) flow += !used[i] && dfs(i);
      ret += flow;
    } while (flow);
    return ret;
  }
};

vector<size_t> extract_subset(const vector<size_t>& all, const int subset) {
  vector<size_t> res;
  for (int i = 0; i < (int)all.size(); i++)
    if (subset & (1 << i)) res.push_back(all[i]);
  return res;
}

vector<size_t> read_algorithms() {
  int A;
  cin >> A;
  set<size_t> algo;
  while (A--) {
    string a;
    cin >> a;
    algo.emplace(hasher(a));
  }
  return vector<size_t>{algo.begin(), algo.end()};
}

int main() {
  int N;

  while (cin >> N) {
    map<vector<size_t>, int> node_idx;
    vector<pair<int, int>> edges;

    const auto get_node_idx = [&](const vector<size_t>& algo_idx_list) -> int {
      if (!node_idx.count(algo_idx_list)) node_idx[algo_idx_list] = node_idx.size();
      return node_idx[algo_idx_list];
    };

    for (int t = 0; t < N; t++) {
      const vector<size_t> can_teach = read_algorithms();

      for (int subset = 1; subset < (1 << can_teach.size()); subset++) {
        const vector<size_t> algo_subset = extract_subset(can_teach, subset);

        const int v = get_node_idx(algo_subset);

        for (int i = 0; i < (int)algo_subset.size(); i++) {
          const vector<size_t> remove_one = extract_subset(algo_subset, ~(1 << i));
          const int u = get_node_idx(remove_one);
          edges.emplace_back(u, v);
        }
      }
    }

    HopcroftKarp hk(node_idx.size(), node_idx.size());

    for (const auto& [u, v] : edges) {
      hk.add_edge(u, v);
    }

    cout << node_idx.size() - hk.max_bipartite_matching() << endl;
  }
}
