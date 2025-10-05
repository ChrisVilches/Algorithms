#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;
  using pii = pair<int, int>;

 public:
  vector<ll> findXSum(const vector<int>& nums, const int k, const size_t x) {
    const int n = nums.size();
    vector<ll> ans;
    ll curr_sum = 0;

    unordered_map<int, int> freq;
    set<pii> on, off;

    const auto enable = [&](const pii p) {
      curr_sum += static_cast<ll>(p.first) * p.second;
      on.insert(p);
    };

    const auto disable = [&](const pii p) {
      if (on.erase(p) != 0) curr_sum -= static_cast<ll>(p.first) * p.second;
    };

    const auto put = [&](const int val, const int inc) {
      const pii curr_elem{freq[val], val};

      disable(curr_elem);
      off.erase(curr_elem);
      freq[val] += inc;
      off.emplace(freq[val], val);

      const pii largest_off = *off.rbegin();

      if (on.size() < x) {
        off.erase(largest_off);
        enable(largest_off);
      } else {
        const pii smallest_on = *on.begin();
        if (smallest_on < largest_off) {
          off.erase(largest_off);
          disable(smallest_on);
          enable(largest_off);
          off.insert(smallest_on);
        }
      }
    };

    for (int i = 0; i < k; i++) put(nums[i], 1);

    for (int i = 0; i < n - k + 1; i++) {
      ans.emplace_back(curr_sum);
      put(nums[i], -1);
      if (i + k < n) put(nums[i + k], 1);
    }

    return ans;
  }
};
