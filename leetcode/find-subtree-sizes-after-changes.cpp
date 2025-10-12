#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<vector<int>> make_graph(const vector<int>& parent) {
    vector<vector<int>> graph(parent.size());

    for (int i = 1; i < (int)graph.size(); i++) {
      graph[parent[i]].emplace_back(i);
    }

    return graph;
  }

 public:
  vector<int> findSubtreeSizes(vector<int>& parent, const string s) {
    vector<int> ans(parent.size());
    const vector<vector<int>> graph = make_graph(parent);

    map<char, stack<int>> char_map;

    const function<void(int)> dfs = [&](const int u) {
      const char curr_char = s[u];

      if (!char_map[curr_char].empty()) {
        parent[u] = char_map[curr_char].top();
      }

      char_map[curr_char].push(u);
      for (const int v : graph[u]) {
        dfs(v);
      }
      assert(!char_map[curr_char].empty());
      char_map[curr_char].pop();
    };

    dfs(0);

    const vector<vector<int>> new_graph = make_graph(parent);

    const function<int(int)> dfs_dist = [&](const int u) {
      ans[u] = 1;
      for (const int v : new_graph[u]) {
        ans[u] += dfs_dist(v);
      }
      return ans[u];
    };

    dfs_dist(0);

    return ans;
  }
};
