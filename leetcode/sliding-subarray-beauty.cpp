#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> getSubarrayBeauty(const vector<int>& nums, const int k, const int x) {
    const int n = nums.size();
    vector<int> ans(n - k + 1);

    unordered_map<int, int> freq;

    for (const int val : nums | std::views::take(k)) {
      freq[val]++;
    }

    for (int i = 0; i < n - k + 1; i++) {
      ans[i] = 0;

      for (int v = -50, rem = x; v <= 0; v++) {
        rem -= freq[v];

        if (rem <= 0) {
          ans[i] = v;
          break;
        }
      }

      freq[nums[i]]--;
      if (i + k < n) freq[nums[i + k]]++;
    }

    return ans;
  }
};
