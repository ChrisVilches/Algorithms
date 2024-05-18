#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<pair<int, bool>> events;
    for (const auto& interval : intervals) {
      events.emplace_back(interval[0], false);
      events.emplace_back(interval[1], true);
    }

    sort(events.begin(), events.end());

    int left = 0;
    int curr = 0;
    vector<vector<int>> ans;

    for (const auto& [x, exit] : events) {
      if (exit) {
        curr--;
        if (curr == 0) {
          ans.push_back({left, x});
        }

      } else {
        if (curr == 0) {
          left = x;
        }
        curr++;
      }
    }

    return ans;
  }
};
