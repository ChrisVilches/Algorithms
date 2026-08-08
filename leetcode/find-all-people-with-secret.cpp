#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> findAllPeople(const int n, const vector<vector<int>>& meetings,
                            const int firstPerson) {
    map<int, unordered_map<int, unordered_set<int>>> times;

    for (const vector<int>& m : meetings) {
      times[m.back()][m[0]].emplace(m[1]);
      times[m.back()][m[1]].emplace(m[0]);
    }

    unordered_set<int> ans;
    ans.emplace(0);
    ans.emplace(firstPerson);

    for (auto& [_, graph] : times) {
      queue<int> q;

      for (auto& [u, adj] : graph) {
        if (!ans.count(u)) continue;

        for (const int v : adj) q.emplace(v);
        adj.clear();
      }

      while (!q.empty()) {
        const int u = q.front();
        q.pop();
        ans.emplace(u);

        for (const int v : graph[u]) {
          if (ans.count(v)) continue;
          q.emplace(v);
        }
      }
    }

    return {ans.begin(), ans.end()};
  }
};
