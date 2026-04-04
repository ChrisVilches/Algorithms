#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> findSmallestSetOfVertices(const int n, const vector<vector<int>>& edges) {
    unordered_set<int> s;
    for (int u = 0; u < n; u++) s.emplace(u);

    for (const vector<int>& edge : edges) {
      s.erase(edge.back());
    }

    return {s.begin(), s.end()};
  }
};
