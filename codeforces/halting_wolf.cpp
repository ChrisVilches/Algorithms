#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, ll> pii;

template <unsigned int V>
struct FordFulkerson {
  FordFulkerson(const vector<vector<pii>>& graph) {
    original_graph = graph;

    memset(g, 0, sizeof g);

    for (int u = 0; u < (int)original_graph.size(); u++)
      for (const auto& [v, c] : original_graph[u]) g[u][v] = c;
  }

  ll calculate_flow(const int s, const int t) {
    int u, v;
    ll max_flow = 0;

    memcpy(rgraph, g, sizeof g);

    while (bfs(s, t)) {
      ll path_flow = LONG_LONG_MAX;
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
  ll g[V][V], rgraph[V][V], parent[V];
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

tuple<int, int, vector<vector<pii>>> read_network_graph(const int N) {
  vector<vector<pii>> graph(N + 1);

  string in;
  int n, v;
  const int sink = N;

  auto transform_v = [sink](int& v) -> void {
    v--;
    if (v == 0) v = sink;
  };

  for (int u = 0; u < N; u++) {
    cin >> in;

    if (in[0] == '*') {
      cin >> v;
      transform_v(v);
      graph[u].push_back({v, LONG_LONG_MAX});
    } else {
      stringstream ss(in);
      ss >> n;
      map<int, int> edges;

      while (n--) {
        cin >> v;
        transform_v(v);
        edges[v]++;
      }

      for (auto const [v, c] : edges) graph[u].push_back({v, c});
    }
  }

  return {0, sink, graph};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N) {
    const auto [source, sink, graph] = read_network_graph(N);

    FordFulkerson<101> ff(graph);

    ll flow = ff.calculate_flow(source, sink);

    if (flow == LONG_LONG_MAX) {
      cout << "*" << endl;
    } else {
      cout << flow + 1 << endl;
    }
  }
}
