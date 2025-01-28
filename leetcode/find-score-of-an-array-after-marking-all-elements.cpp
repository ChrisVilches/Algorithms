#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long findScore(const vector<int>& nums) {
    const int n = nums.size();
    set<pair<int, int>> s;

    for (int i = 0; i < n; i++) {
      s.emplace(nums[i], i);
    }

    long long ans = 0;

    while (!s.empty()) {
      const auto [score, idx] = *s.begin();
      ans += score;

      s.erase(s.begin());

      if (idx > 0) s.erase({nums[idx - 1], idx - 1});
      if (idx < n - 1) s.erase({nums[idx + 1], idx + 1});
    }

    return ans;
  }
};
