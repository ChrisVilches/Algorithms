#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findCenter(vector<vector<int>>& edges) {
    set<int> present;
    for (const auto& edge : edges) {
      const int u = edge.front();
      const int v = edge.back();
      if (present.count(u)) return u;
      if (present.count(v)) return v;
      present.emplace(u);
      present.emplace(v);
    }
    return -1;
  }
};
