#include <bits/stdc++.h>
using namespace std;

class Solution {
  int solve(const vector<int>& start1, const vector<int>& duration1,
            const vector<int>& start2, const vector<int>& duration2) {
    int res = INT_MAX;
    int earliest_first = INT_MAX;

    for (const auto& [s, d] : views::zip(start1, duration1)) {
      earliest_first = min(earliest_first, s + d);
    }

    for (const auto& [s, d] : views::zip(start2, duration2)) {
      const int start_time = max(earliest_first, s);
      res = min(res, start_time + d);
    }

    return res;
  }

 public:
  int earliestFinishTime(const vector<int>& land_start, const vector<int>& land_duration,
                         const vector<int>& water_start,
                         const vector<int>& water_duration) {
    return min(solve(land_start, land_duration, water_start, water_duration),
               solve(water_start, water_duration, land_start, land_duration));
  }
};
