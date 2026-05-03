#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isBipartite(const vector<vector<int>>& graph) {
    vector<int> group(graph.size(), -1);

    for (size_t i = 0; i < graph.size(); i++) {
      if (group[i] != -1) continue;

      queue<int> q;
      q.emplace(i);
      group[i] = 0;

      while (!q.empty()) {
        const int u = q.front();
        q.pop();

        for (const int v : graph[u]) {
          if (group[u] == group[v]) return false;
          if (group[v] != -1) continue;

          group[v] = !group[u];
          q.emplace(v);
        }
      }
    }

    return true;
  }
};
