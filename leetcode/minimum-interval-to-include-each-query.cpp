#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
    vector<tuple<int, int, int>> events;

    const auto get_count = [&](const int i) {
      const int left = intervals[i][0];
      const int right = intervals[i][1];
      return right - left + 1;
    };

    for (int i = 0; i < (int)intervals.size(); i++) {
      const int left = intervals[i][0];
      const int right = intervals[i][1];
      events.emplace_back(left, 0, i);
      events.emplace_back(right, 2, i);
    }

    for (int i = 0; i < (int)queries.size(); i++) {
      events.emplace_back(queries.at(i), 1, i);
    }

    sort(events.begin(), events.end());

    vector<int> ans(queries.size(), -1);

    multiset<int> curr_counts;

    for (const auto& [_, type, idx] : events) {
      switch (type) {
        case 0:
          curr_counts.emplace(get_count(idx));
          break;
        case 1:
          if (!curr_counts.empty()) {
            ans[idx] = *curr_counts.begin();
          }
          break;
        default:
          const auto it = curr_counts.find(get_count(idx));
          curr_counts.erase(it);
      }
    }

    return ans;
  }
};
