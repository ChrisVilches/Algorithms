#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> findDisappearedNumbers(vector<int>& nums) {
    const int n = nums.size();

    vector<int> ans;

    for (int x : nums) {
      x = abs(x);
      nums[x - 1] = -abs(nums[x - 1]);
    }

    for (int i = 0; i < n; i++) {
      if (nums[i] > 0) ans.emplace_back(i + 1);
    }

    return ans;
  }
};
