#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minTaps(const int n, const vector<int>& ranges) {
    vector<pair<int, int>> intervals;

    int ans = 1;
    int next_right = 0;
    int right = -1;

    for (size_t i = 0; i < ranges.size(); i++) {
      const int a = i - ranges[i];
      const int b = i + ranges[i];
      if (a <= 0) {
        right = max(right, b);
      } else {
        intervals.emplace_back(a, b);
      }
    }

    if (right == -1) return -1;

    sort(intervals.begin(), intervals.end());

    for (const auto& [l, r] : intervals) {
      if (right < l) {
        ans++;
        right = next_right;
      }

      if (l <= right) {
        next_right = max(next_right, r);
      }
    }

    if (right >= n) return ans;

    return next_right >= n ? ans + 1 : -1;
  }
};
