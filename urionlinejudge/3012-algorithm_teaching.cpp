#include <bits/stdc++.h>
using namespace std;

// TODO: Refactor?

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
      int a = q.front();
      q.pop();
      for (auto& b : graph[a]) {
        int c = match[b];
        if (c >= 0 && dist[c] == -1) dist[c] = dist[a] + 1, q.emplace(c);
      }
    }
  }

  bool dfs(int a) {
    visited[a] = true;
    for (auto& b : graph[a]) {
      int c = match[b];
      if (c < 0 || (!visited[c] && dist[c] == dist[a] + 1 && dfs(c))) {
        match[b] = a, used[a] = true;
        return true;
      }
    }
    return false;
  }

 public:
  HopcroftKarp(int n, int m) : graph(n), match(m, -1), used(n) {}

  void add_edge(int u, int v) { graph[u].push_back(v); }

  int max_bipartite_matching() {
    int flow, ret = 0;
    do {
      bfs();
      visited.assign(graph.size(), false);
      flow = 0;
      for (int i = 0; i < (int)graph.size(); i++) flow += !used[i] && dfs(i);
      ret += flow;
    } while (flow);
    return ret;
  }
};

int main() {
  int N;

  while (cin >> N) {
    map<string, int> algo_idx;
    map<vector<int>, int> node_idx;
    vector<pair<int, int>> edges;

    const auto get_node_idx = [&](const vector<int>& algo_idx_list) -> int {
      if (!node_idx.count(algo_idx_list)) node_idx[algo_idx_list] = node_idx.size();
      return node_idx[algo_idx_list];
    };

    for (int t = 0; t < N; t++) {
      int A;
      cin >> A;
      vector<int> can_teach;

      for (int i = 0; i < A; i++) {
        string a;
        cin >> a;

        algo_idx.count(a) || algo_idx.emplace(a, algo_idx.size()).second;

        can_teach.push_back(algo_idx[a]);
      }

      sort(can_teach.begin(), can_teach.end());

      for (int subset = 1; subset < (1 << A); subset++) {
        vector<int> algo_idx_list;

        for (int j = 0; j < A; j++)
          if (subset & (1 << j)) algo_idx_list.push_back(can_teach[j]);

        const int v = get_node_idx(algo_idx_list);

        for (int j = 0; j < (int)algo_idx_list.size(); j++) {
          vector<int> algo_idx_list2 = algo_idx_list;
          algo_idx_list2.erase(algo_idx_list2.begin() + j);
          edges.emplace_back(get_node_idx(algo_idx_list2), v);
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
