#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findMinArrowShots(const vector<vector<int>>& points) {
    vector<tuple<int, bool, int>> events;

    for (size_t i = 0; i < points.size(); i++) {
      const int start = points[i].front();
      const int end = points[i].back();
      events.emplace_back(start, false, i);
      events.emplace_back(end, true, i);
    }

    sort(events.begin(), events.end());

    int ans = 0;

    vector<int> curr;
    vector<bool> done(points.size(), false);

    for (const auto& [_, exit, idx] : events) {
      if (done[idx]) continue;

      if (exit) {
        ans++;

        while (!curr.empty()) {
          done[curr.back()] = true;
          curr.pop_back();
        }
      } else {
        curr.emplace_back(idx);
      }
    }

    return ans;
  }
};
