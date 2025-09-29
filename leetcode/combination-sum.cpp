#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> nums;
  vector<vector<int>> ans;
  vector<int> curr;

  void search(const size_t idx, const int rem) {
    curr.emplace_back(nums[idx]);
    const int new_rem = rem - nums[idx];

    if (new_rem == 0) {
      ans.emplace_back(curr);
    } else if (new_rem > 0) {
      for (size_t i = idx; i < nums.size(); i++) {
        search(i, new_rem);
      }
    }

    curr.pop_back();
  }

 public:
  vector<vector<int>> combinationSum(const vector<int>& candidates, const int target) {
    this->nums = candidates;

    for (size_t i = 0; i < nums.size(); i++) {
      search(i, target);
    }

    return ans;
  }
};
