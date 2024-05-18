#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maximumDetonation(vector<vector<int>>& bombs) {
    const int n = bombs.size();
    vector<vector<int>> graph(n);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) continue;

        const double dx = bombs[i][0] - bombs[j][0];
        const double dy = bombs[i][1] - bombs[j][1];
        const double dist = hypot(dx, dy);

        if (dist <= bombs[i][2]) {
          graph[i].emplace_back(j);
        }
      }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
      set<int> visited;

      queue<int> q;
      q.emplace(i);

      while (!q.empty()) {
        const int u = q.front();
        q.pop();
        visited.emplace(u);
        for (const int v : graph[u]) {
          if (visited.count(v)) continue;
          q.emplace(v);
          visited.emplace(v);
        }
      }

      ans = max(ans, (int)visited.size());
    }

    return ans;
  }
};
