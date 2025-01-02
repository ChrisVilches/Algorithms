#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;

  vector<ll> make_asc(const vector<int>& nums) {
    stack<int> s;
    vector<ll> res(nums.size());

    for (int i = 0; i < (int)nums.size(); i++) {
      const ll x = nums[i];

      while (!s.empty() && nums[s.top()] > x) s.pop();

      if (s.empty()) {
        res[i] = x * (i + 1);
      } else {
        res[i] = res[s.top()] + (x * (i - s.top()));
      }

      s.push(i);
    }

    return res;
  }

 public:
  long long maximumSumOfHeights(vector<int> nums) {
    const int n = nums.size();
    if (n < 3) {
      return accumulate(nums.begin(), nums.end(), 0);
    }

    const vector<ll> asc = make_asc(nums);
    reverse(nums.begin(), nums.end());
    vector<ll> desc = make_asc(nums);
    reverse(desc.begin(), desc.end());

    ll ans = 0;

    for (int i = 1; i < n - 1; i++) {
      ans = max(ans, asc[i] + desc[i + 1]);
      ans = max(ans, asc[i - 1] + desc[i]);
    }

    return ans;
  }
};
