#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;

 public:
  long long maxAlternatingSum(vector<int>& nums) {
    ll ans = nums.front();
    ll min_val = nums.front();

    for (const ll x : nums) {
      const ll sum = x + ans - min_val;

      if (sum > ans) {
        ans = sum;
        min_val = ans;
      }

      min_val = min(min_val, x);
    }

    return ans;
  }
};
