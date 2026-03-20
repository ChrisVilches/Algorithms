#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int buttonWithLongestTime(const vector<vector<int>>& events) {
    int idx = events.front().front();
    int time = events.front().back();

    for (size_t i = 1; i < events.size(); i++) {
      const int prev_time = events[i].back() - events[i - 1].back();

      if (prev_time == time) {
        idx = min(idx, events[i].front());
      } else if (prev_time > time) {
        time = prev_time;
        idx = events[i].front();
      }
    }

    return idx;
  }
};
