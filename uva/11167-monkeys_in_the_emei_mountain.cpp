#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

struct Monkey {
  int v, a, b, node_idx;
};

struct Period {
  Period(int t) : start(t) {}
  int start, end = -1, node_idx = -1;
  int length() const { return end - start; }
};

int N, M;

vector<Monkey> monkeys;
map<int, Period> periods;

template <unsigned int V>
struct FordFulkerson {
  FordFulkerson(const vector<vector<pii>>& graph) {
    original_graph = graph;

    memset(g, 0, sizeof g);

    for (int u = 0; u < (int)original_graph.size(); u++)
      for (const auto& [v, c] : original_graph[u]) g[u][v] = c;
  }

  int edge_flow(const int u, const int v) const { return g[u][v] - rgraph[u][v]; }

  int calculate_flow(const int s, const int t) {
    int u, v, max_flow = 0;

    memcpy(rgraph, g, sizeof g);

    while (bfs(s, t)) {
      int path_flow = INT_MAX;
      for (v = t; v != s; v = parent[v]) {
        u = parent[v];
        path_flow = min(path_flow, rgraph[u][v]);
      }

      for (v = t; v != s; v = parent[v]) {
        u = parent[v];
        rgraph[u][v] -= path_flow;
        rgraph[v][u] += path_flow;
      }

      max_flow += path_flow;
    }

    return max_flow;
  }

 private:
  int g[V][V], rgraph[V][V], parent[V];
  bool visited[V];
  vector<vector<pii>> original_graph;

  bool bfs(const int s, const int t) {
    memset(visited, 0, sizeof visited);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (auto [v, _] : original_graph[u]) {
        if (!visited[v] && rgraph[u][v] > 0) {
          if (v == t) {
            parent[v] = u;
            return true;
          }
          q.push(v);
          parent[v] = u;
          visited[v] = true;
        }
      }
    }

    return false;
  }
};

tuple<int, int, vector<vector<pii>>> build_graph() {
  vector<vector<pii>> graph;

  auto add_edge = [&](int u, int v, int c) -> void {
    graph[u].push_back({v, c});
    graph[v].push_back({u, 0});
  };

  auto add_node = [&]() -> int {
    graph.push_back(vector<pii>());
    return graph.size() - 1;
  };

  const int source = add_node();
  const int sink = add_node();

  for (const Monkey& m : monkeys) {
    periods.emplace(m.a, m.a);
    periods.emplace(m.b, m.b);
  }

  for (auto it = periods.begin(); next(it) != periods.end(); it++) {
    Period& curr_period = it->second;
    Period next_period = next(it)->second;
    curr_period.end = next_period.start;
    curr_period.node_idx = add_node();
    add_edge(curr_period.node_idx, sink, M * curr_period.length());
  }

  periods.erase(prev(periods.end()));

  for (Monkey& m : monkeys) {
    m.node_idx = add_node();
    add_edge(source, m.node_idx, m.v);

    for (int t = m.a; t < m.b;) {
      const Period& period = periods.at(t);
      add_edge(m.node_idx, period.node_idx, period.length());
      t = period.end;
    }
  }

  return {source, sink, graph};
}

vector<pii> group_numbers(vector<int>& nums) {
  sort(nums.begin(), nums.end());

  vector<pii> res;

  for (int n : nums)
    if (!res.empty() && res.back().second + 1 == n)
      res.back().second = n;
    else
      res.push_back({n, n});

  return res;
}

vector<vector<pii>> get_allocation(const FordFulkerson<1000>& ff) {
  vector<int> available(periods.rbegin()->second.end, M);

  map<int, vector<int>> solutions;

  for (const auto& [_, period] : periods) {
    set<pii> monkeys_to_allocate;

    for (const Monkey& monkey : monkeys) {
      int flow = ff.edge_flow(monkey.node_idx, period.node_idx);
      if (flow > 0) monkeys_to_allocate.emplace(flow, monkey.node_idx);
    }

    int t = period.start;

    for (const auto& [flow, monkey_idx] : monkeys_to_allocate)
      for (int f = 0; f < flow; t++) {
        if (t == period.end) t = period.start;
        if (available[t] == 0) continue;

        solutions[monkey_idx].push_back(t);
        available[t]--;
        f++;
      }
  }

  vector<vector<pii>> res;

  for (auto& [_, solution] : solutions) res.push_back(group_numbers(solution));

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int test_case = 1;

  while (cin >> N >> M && N) {
    int total_required = 0;

    monkeys.assign(N, Monkey());
    periods.clear();

    for (int i = 0; i < N; i++) {
      cin >> monkeys[i].v >> monkeys[i].a >> monkeys[i].b;
      total_required += monkeys[i].v;
    }

    const auto [source, sink, graph] = build_graph();

    FordFulkerson<1000> ff(graph);

    const bool has_solution = total_required == ff.calculate_flow(source, sink);

    cout << "Case " << (test_case++) << ": " << (has_solution ? "Yes" : "No") << endl;

    if (!has_solution) continue;

    for (auto& alloc : get_allocation(ff)) {
      cout << alloc.size();
      for (const auto& [a, b] : alloc) cout << " (" << a << "," << b + 1 << ")";
      cout << endl;
    }
  }
}
