#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;

 public:
  int minSubarray(const vector<int>& nums, const int p) {
    const int n = nums.size();
    const int target = accumulate(nums.begin(), nums.end(), 0LL) % p;

    if (target == 0) return 0;

    int ans = n;
    unordered_map<int, int> last_seen;
    last_seen[0] = -1;

    ll prefix_sum = 0;

    for (int i = 0; i < n; i++) {
      prefix_sum += nums[i];
      const int curr_mod = prefix_sum % p;
      const int needed = (curr_mod - target + p) % p;

      if (last_seen.count(needed)) {
        ans = min(ans, i - last_seen[needed]);
      }

      last_seen[curr_mod] = i;
    }

    return ans == n ? -1 : ans;
  }
};
