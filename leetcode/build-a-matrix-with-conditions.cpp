#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> toposort_or_find_cycle(const vector<vector<int>>& graph) const {
    enum State { UNVISITED, VISITING, VISITED };
    vector<State> state(graph.size(), UNVISITED);
    vector<int> order;
    stack<pair<int, bool>> dfs;

    for (size_t i = 0; i < graph.size(); ++i) {
      if (state[i] != UNVISITED) continue;
      dfs.emplace(i, false);

      while (!dfs.empty()) {
        const auto [u, post] = dfs.top();
        dfs.pop();

        if (post) {
          state[u] = VISITED;
          order.emplace_back(u);
        } else if (state[u] == VISITING) {
          return {};
        } else if (state[u] == UNVISITED) {
          state[u] = VISITING;
          dfs.emplace(u, true);
          for (int v : graph[u])
            if (state[v] != VISITED) dfs.emplace(v, false);
        }
      }
    }

    reverse(order.begin(), order.end());
    return order;
  }

  vector<int> sort(const int k, const vector<vector<int>>& edges) const {
    vector<vector<int>> graph(k);

    for (const auto& edge : edges) {
      graph[edge.front() - 1].emplace_back(edge.back() - 1);
    }

    auto res = toposort_or_find_cycle(graph);

    for (int& x : res) x++;
    return res;
  }

 public:
  vector<vector<int>> buildMatrix(const int k, const vector<vector<int>>& rowConditions,
                                  const vector<vector<int>>& colConditions) {
    const auto row_sort = sort(k, rowConditions);
    const auto col_sort = sort(k, colConditions);

    if (row_sort.empty() || col_sort.empty()) return {};

    vector<vector<int>> res(k, vector<int>(k, 0));

    vector<int> col_idx(k + 1);

    for (int i = 0; i < k; i++) {
      const int val = col_sort[i];
      col_idx[val] = i;
    }

    for (int i = 0; i < k; i++) {
      const int val = row_sort[i];
      const int j = col_idx[val];
      res[i][j] = val;
    }

    return res;
  }
};
