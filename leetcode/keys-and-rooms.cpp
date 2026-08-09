#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool canVisitAllRooms(const vector<vector<int>>& rooms) {
    const int n = rooms.size();
    vector<vector<int>> graph(n);

    for (int i = 0; i < n; i++) {
      for (const int k : rooms[i]) graph[i].emplace_back(k);
    }

    vector<bool> vis(n, false);

    const function<void(int)> dfs = [&](const int u) {
      if (vis[u]) return;
      vis[u] = true;

      for (const int v : graph[u]) dfs(v);
    };

    dfs(0);

    return accumulate(vis.begin(), vis.end(), 0) == n;
  }
};
