#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int boxDelivering(const vector<vector<int>>& boxes, const int ports_count,
                    const int max_boxes, const int max_weight) {
    const int n = boxes.size();

    vector<int> psum_trips{0};

    for (int i = 1; i < n; i++) {
      const int add = boxes[i - 1].front() != boxes[i].front();
      psum_trips.emplace_back(psum_trips.back() + add);
    }

    set<pair<int, int>> order;
    vector<int> dp(n, INT_MAX);
    dp[n - 1] = 2;

    int j = n - 1;
    int weight = 0;

    const auto toggle = [&](const int i, const bool add) {
      const int value = psum_trips[i] + (i + 1 < n ? dp[i + 1] : 0);
      const pair<int, int> elem{value, i};
      if (add) {
        order.emplace(value, i);
        weight += boxes[i].back();
      } else {
        order.erase({value, i});
        weight -= boxes[i].back();
      }
    };

    toggle(n - 1, true);

    for (int i = n - 2; i >= 0; i--) {
      toggle(i, true);

      while (j - i + 1 > max_boxes || weight > max_weight) {
        toggle(j--, false);
      }

      const auto [_, idx] = *order.begin();
      const int trips = psum_trips[idx] - psum_trips[i];

      dp[i] = 2 + trips + (idx + 1 < n ? dp[idx + 1] : 0);
    }

    return dp.front();
  }
};
