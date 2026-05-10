#include <bits/stdc++.h>
using namespace std;

class Solution {
  using pii = pair<int, int>;

  struct Hash {
    size_t operator()(const pii& p) const noexcept {
      return (static_cast<uint64_t>(p.first) << 20) | static_cast<uint64_t>(p.second);
    }
  };

 public:
  int minimumCost(const vector<int>& start, const vector<int>& target,
                  const vector<vector<int>>& special_roads) {
    const pii src{start.front(), start.back()};
    const pii dest{target.front(), target.back()};

    unordered_map<pii, vector<pair<pii, int>>, Hash> graph;
    unordered_map<pii, int, Hash> dist;
    unordered_set<pair<int, int>, Hash> all;
    all.emplace(src);
    all.emplace(dest);

    for (const vector<int>& road : special_roads) {
      const pii u{road[0], road[1]};
      const pii v{road[2], road[3]};
      const int cost = road[4];
      graph[u].emplace_back(v, cost);
      all.emplace(u);
      all.emplace(v);
    }

    priority_queue<pair<int, pii>> pq;
    pq.emplace(0, src);
    dist[src] = 0;

    while (!pq.empty()) {
      const auto [_, u] = pq.top();
      pq.pop();

      if (u == dest) break;

      for (const auto [v, cost] : graph[u]) {
        const int alt = dist[u] + cost;
        if (!dist.count(v) || alt < dist[v]) {
          dist[v] = alt;
          pq.emplace(-alt, v);
        }
      }

      for (const pii& v : all) {
        const int alt = dist[u] + abs(u.first - v.first) + abs(u.second - v.second);
        if (!dist.count(v) || alt < dist[v]) {
          dist[v] = alt;
          pq.emplace(-alt, v);
        }
      }
    }

    return dist[dest];
  }
};
