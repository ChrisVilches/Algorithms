#include <bits/stdc++.h>
using namespace std;

class Solution {
  using pii = pair<int, int>;

 public:
  int networkDelayTime(const vector<vector<int>>& times, const int n, const int k) {
    vector<vector<pii>> graph(n);

    for (const vector<int>& edge : times) {
      const int u = edge[0];
      const int v = edge[1];
      const int w = edge[2];
      graph[u - 1].emplace_back(v - 1, w);
    }

    priority_queue<pii> pq;

    vector<int> dist(n, INT_MAX);
    pq.emplace(0, k - 1);
    dist[k - 1] = 0;

    while (!pq.empty()) {
      const auto [_, u] = pq.top();
      pq.pop();

      for (const auto& [v, w] : graph[u]) {
        const int alt = dist[u] + w;
        if (alt < dist[v]) {
          dist[v] = alt;
          pq.emplace(-alt, v);
        }
      }
    }

    const int res = *max_element(dist.begin(), dist.end());
    return res == INT_MAX ? -1 : res;
  }
};
