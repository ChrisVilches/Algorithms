#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> fallingSquares(vector<vector<int>>& positions) {
    vector<int> ans;

    map<int, int> intervals;

    for (const auto& pos : positions) {
      const int x0 = pos[0];
      const int x1 = x0 + pos[1];
      const int h = pos[1];

      int tallest = 0;
      auto it = intervals.lower_bound(x0);

      if (!intervals.empty() && it != intervals.begin()) it--;

      int last = 0;

      while (it != intervals.end() && it->first < x1) {
        const auto next_it = next(it);
        const auto [it_x, it_h] = *it;

        if (x0 < it_x + it_h) {
          tallest = max(tallest, it_h);
          last = it_h;
        }

        if (x0 <= it_x) intervals.erase(it);

        it = next_it;
      }

      if (!intervals.count(x1)) intervals[x1] = last;

      const int new_height = tallest + h;

      intervals[x0] = new_height;
      ans.emplace_back(new_height);
    }

    for (int i = 1; i < (int)ans.size(); i++) {
      ans[i] = max(ans[i], ans[i - 1]);
    }

    return ans;
  }
};
