#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minJumps(vector<int>& arr) {
    map<int, vector<int>> value_idx;

    for (int i = 0; i < (int)arr.size(); i++) {
      value_idx[arr[i]].push_back(i);
    }

    vector<bool> visited(arr.size(), false);

    queue<pair<int, int>> q;
    q.emplace(0, 0);

    while (!q.empty()) {
      const auto [u, dist] = q.front();
      q.pop();
      visited[u] = true;

      if (u == (int)arr.size() - 1) return dist;

      vector<int>& same = value_idx[arr[u]];
      set<int> nodes{same.begin(), same.end()};
      nodes.insert(u - 1);
      nodes.insert(u + 1);
      same.clear();

      for (const auto v : nodes) {
        if (v < 0 || v >= (int)arr.size()) continue;
        if (visited[v]) continue;

        q.emplace(v, dist + 1);
        visited[v] = true;
      }
    }

    return -1;
  }
};
