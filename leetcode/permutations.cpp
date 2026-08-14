#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> permute(const vector<int>& nums) {
    vector<vector<int>> ans;
    vector<int> curr;
    bitset<6> s;

    const function<void()> recur = [&]() {
      if (s.count() == nums.size()) {
        ans.emplace_back(curr);
        return;
      }

      for (size_t i = 0; i < nums.size(); i++) {
        if (s[i]) continue;

        curr.emplace_back(nums[i]);
        s.set(i);

        recur();

        s.reset(i);
        curr.pop_back();
      }
    };

    recur();

    return ans;
  }
};
