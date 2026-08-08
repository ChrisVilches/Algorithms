#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> intervalIntersection(const vector<vector<int>>& list1,
                                           const vector<vector<int>>& list2) {
    vector<pair<int, bool>> events;

    for (const auto& list : {list1, list2}) {
      for (const auto& interval : list) {
        events.emplace_back(interval.front(), false);
        events.emplace_back(interval.back(), true);
      }
    }

    sort(events.begin(), events.end());

    vector<vector<int>> ans;

    int curr = 0;

    for (const auto& [x, exit] : events) {
      if (curr == 1 && !exit) ans.push_back({x, x});
      if (curr == 2) ans.back().back() = x;

      curr += exit ? -1 : 1;
    }

    return ans;
  }
};
