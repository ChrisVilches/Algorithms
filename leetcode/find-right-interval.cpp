#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> findRightInterval(const vector<vector<int>>& intervals) {
    map<int, int> interval_map;

    for (size_t i = 0; i < intervals.size(); i++) {
      interval_map[intervals[i].front()] = i;
    }

    vector<int> ans(intervals.size(), -1);

    for (size_t i = 0; i < intervals.size(); i++) {
      const int end = intervals[i].back();
      const auto it = interval_map.lower_bound(end);
      if (it == interval_map.end()) continue;

      ans[i] = it->second;
    }

    return ans;
  }
};
