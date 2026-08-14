#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  double maxProbability(const int n, vector<vector<int>>& edges,
                        const vector<double>& prob, const int src, const int dest) {
    vector<vector<pair<int, double>>> graph(n);

    for (size_t i = 0; i < edges.size(); i++) {
      const int u = edges[i].front();
      const int v = edges[i].back();
      graph[u].emplace_back(v, prob[i]);
      graph[v].emplace_back(u, prob[i]);
    }

    vector<double> dist(n, 0);
    dist[src] = 1;

    priority_queue<pair<double, int>> pq;
    pq.emplace(1, src);

    while (!pq.empty()) {
      const auto [_, u] = pq.top();
      pq.pop();

      for (const auto& [v, p] : graph[u]) {
        const double alt = p * dist[u];
        if (alt > dist[v]) {
          dist[v] = alt;
          pq.emplace(alt, v);
        }
      }
    }

    return dist[dest];
  }
};
