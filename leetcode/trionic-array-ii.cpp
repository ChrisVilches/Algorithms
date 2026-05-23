#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;

  ll calculate_asc(const vector<int>& nums, const bool left) {
    ll res = LLONG_MIN;
    ll sum = 0;

    if (left) {
      for (const ll x : views::drop(nums, 1)) {
        sum += x;
        res = max(res, sum);
      }
    } else {
      for (const ll x : nums | views::take(nums.size() - 1) | views::reverse) {
        sum += x;
        res = max(res, sum);
      }
    }

    return res;
  }

 public:
  ll maxSumTrionic(vector<int>& nums) {
    nums.emplace_back(nums.back());

    vector<pair<int, vector<int>>> groups;

    for (size_t i = 0; i < nums.size() - 1; i++) {
      const ll x = nums[i + 1] - nums[i];
      const int sgn = (x > 0) - (x < 0);

      if (groups.empty() || groups.back().first != sgn) {
        if (!groups.empty()) groups.back().second.emplace_back(nums[i]);

        groups.emplace_back(sgn, vector<int>{});
      }

      groups.back().second.emplace_back(nums[i]);
    }

    unordered_map<int, ll> desc_sum, asc_left, asc_right;

    for (size_t i = 0; i < groups.size(); i++) {
      const auto& [sgn, vec] = groups[i];
      if (sgn == 0) continue;

      if (sgn == -1) {
        desc_sum[i] = accumulate(vec.begin(), vec.end(), 0LL);
      } else {
        asc_left[i] = calculate_asc(vec, true);
        asc_right[i] = calculate_asc(vec, false);
      }
    }

    ll ans = LLONG_MIN;

    for (size_t i = 0; i < groups.size() - 2; i++) {
      if (groups[i].first != 1) continue;
      if (groups[i + 1].first != -1) continue;
      if (groups[i + 2].first != 1) continue;

      ans = max(ans, asc_right[i] + desc_sum[i + 1] + asc_left[i + 2]);
    }

    return ans;
  }
};
