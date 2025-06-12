#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int numBusesToDestination(const vector<vector<int>>& routes_input, const int source,
                            const int target) {
    if (source == target) return 0;

    vector<set<int>> routes;
    for (const auto& v : routes_input) {
      routes.push_back({v.begin(), v.end()});
    }

    unordered_map<int, set<int>> route_map;

    queue<pair<int, int>> q;
    unordered_set<int> visited;

    for (size_t r = 0; r < routes.size(); r++) {
      for (const int u : routes[r]) {
        route_map[u].emplace(r);
      }

      if (routes[r].count(source)) {
        q.emplace(r, 1);
        visited.emplace(r);
      }
    }

    while (!q.empty()) {
      const auto [r, dist] = q.front();
      q.pop();
      if (routes[r].count(target)) return dist;

      for (const int u : routes[r]) {
        for (const int r2 : route_map[u]) {
          if (visited.count(r2)) continue;
          visited.emplace(r2);
          q.emplace(r2, dist + 1);
        }
      }
    }

    return -1;
  }
};
