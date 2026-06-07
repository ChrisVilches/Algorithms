#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long maximumSubarraySum(const vector<int>& nums, const int k) {
    const int n = nums.size();
    unordered_map<int, int> freq;
    long long curr = 0;
    long long ans = 0;

    for (const int val : nums | std::views::take(k)) {
      freq[val]++;
      curr += val;
    }

    for (int i = 0; i < n - k + 1; i++) {
      if (freq.size() == static_cast<size_t>(k)) ans = max(ans, curr);

      curr -= nums[i];
      freq[nums[i]]--;

      if (freq[nums[i]] == 0) freq.erase(nums[i]);

      if (i + k < n) {
        freq[nums[i + k]]++;
        curr += nums[i + k];
      }
    }

    return ans;
  }
};
