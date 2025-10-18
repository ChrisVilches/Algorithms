#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool validPath(const int n, const vector<vector<int>>& edges, const int source,
                 const int destination) {
    vector<vector<int>> graph(n);
    for (const auto& edge : edges) {
      graph[edge.front()].emplace_back(edge.back());
      graph[edge.back()].emplace_back(edge.front());
    }
    queue<int> q{{source}};
    vector<int> visited(n, false);
    visited[source] = true;
    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      if (u == destination) return true;

      for (const int v : graph[u]) {
        if (visited[v]) continue;
        visited[v] = true;
        q.emplace(v);
      }
    }
    return false;
  }
};
