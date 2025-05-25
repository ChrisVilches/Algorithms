#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<long long>> splitPainting(const vector<vector<int>>& segments) {
    map<int, long long> deltas;

    for (const vector<int>& seg : segments) {
      const int start = seg.front();
      const int end = seg[1];
      const int color = seg.back();

      deltas[start] += color;
      deltas[end] -= color;
    }

    vector<vector<long long>> ans;

    long long curr_color = 0;
    int prev_x = 0;

    for (const auto& [x, d] : deltas) {
      if (curr_color > 0) {
        ans.emplace_back(initializer_list<long long>{prev_x, x, curr_color});
      }

      curr_color += d;
      prev_x = x;
    }

    return ans;
  }
};
