#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool match(const span<const int> nums, const vector<int> pattern) const {
    for (size_t i = 0; i < nums.size() - 1; i++) {
      if (nums[i] < nums[i + 1] && pattern[i] != 1) return false;
      if (nums[i] == nums[i + 1] && pattern[i] != 0) return false;
      if (nums[i] > nums[i + 1] && pattern[i] != -1) return false;
    }

    return true;
  }

 public:
  int countMatchingSubarrays(const vector<int>& nums, const vector<int>& pattern) {
    int ans = 0;

    const span<const int> arr = nums;

    for (size_t i = 0; i < nums.size() - pattern.size(); i++) {
      ans += match(arr.subspan(i, pattern.size() + 1), pattern);
    }

    return ans;
  }
};
