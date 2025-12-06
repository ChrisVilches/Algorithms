#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<vector<int>> make_graph(const vector<vector<int>>& edges) {
    vector<vector<int>> res(edges.size() + 1);

    for (const auto& edge : edges) {
      const int u = edge.front();
      const int v = edge.back();
      res[u].emplace_back(v);
      res[v].emplace_back(u);
    }

    return res;
  }

  vector<int> bicolor(const vector<vector<int>>& graph) {
    vector<int> res(graph.size(), -1);
    queue<int> q;
    q.emplace(0);
    res[0] = 0;
    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      for (const int v : graph[u]) {
        if (res[v] != -1) continue;
        res[v] = !res[u];
        q.emplace(v);
      }
    }

    return res;
  }

 public:
  vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
    const vector<vector<int>> A = make_graph(edges1);
    const vector<vector<int>> B = make_graph(edges2);

    const vector<int> a_color = bicolor(A);
    const vector<int> b_color = bicolor(B);

    array<int, 2> a{0, 0}, b{0, 0};

    for (const int c : a_color) a[c]++;
    for (const int c : b_color) b[c]++;

    vector<int> res;

    for (const int c : a_color) {
      res.emplace_back(a[c] + max(b[0], b[1]));
    }

    return res;
  }
};
