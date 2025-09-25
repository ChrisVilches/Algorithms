#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool possible(vector<int> nums) {
    sort(nums.begin(), nums.end());
    if (nums.size() < 2) return false;
    const int diff = nums[0] - nums[1];

    for (size_t i = 0; i < nums.size() - 1; i++) {
      if (nums[i] - nums[i + 1] != diff) return false;
    }

    return true;
  }

 public:
  vector<bool> checkArithmeticSubarrays(const vector<int>& nums, const vector<int>& l,
                                        const vector<int>& r) {
    vector<bool> ans;

    for (size_t q = 0; q < l.size(); q++) {
      const int from = l[q];
      const int to = r[q];
      vector<int> arr;
      for (int i = from; i <= to; i++) {
        arr.emplace_back(nums[i]);
      }
      ans.emplace_back(possible(arr));
    }

    return ans;
  }
};
