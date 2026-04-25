#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<bool> checkIfPrerequisite(const int numCourses,
                                   const vector<vector<int>>& prerequisites,
                                   const vector<vector<int>>& queries) {
    const int n = numCourses;

    vector<vector<int>> graph(n);

    for (const auto& edge : prerequisites) {
      const int u = edge.front();
      const int v = edge.back();
      graph[u].emplace_back(v);
    }

    vector<set<int>> deps;

    const function<void(int)> dfs = [&](const int u) {
      if (deps.back().count(u)) return;
      deps.back().emplace(u);
      for (const int v : graph[u]) {
        dfs(v);
      }
    };

    for (int i = 0; i < n; i++) {
      deps.emplace_back(set<int>());
      dfs(i);
      deps[i].erase(i);
    }

    vector<bool> ans;

    for (const auto& q : queries) {
      const int u = q.front();
      const int v = q.back();
      ans.emplace_back(deps[u].count(v));
    }

    return ans;
  }
};
