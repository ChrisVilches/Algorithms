#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<long long> distance(vector<int>& nums) {
    vector<long long> ans(nums.size(), 0);

    for (int iter = 0; iter < 2; iter++) {
      unordered_map<int, long long> count, index_sum;

      for (size_t i = 0; i < nums.size(); i++) {
        const int x = nums[i];

        ans[i] += count[x] * i - index_sum[x];

        count[x]++;
        index_sum[x] += i;
      }

      reverse(ans.begin(), ans.end());
      reverse(nums.begin(), nums.end());
    }

    return ans;
  }
};
