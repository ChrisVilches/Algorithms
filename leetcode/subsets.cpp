#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> subsets(vector<int>& nums) {
    const int n = (int)nums.size();

    vector<vector<int>> result;

    for (int subset = 0; subset < (1 << n); subset++) {
      vector<int> subset_list;

      for (int i = 0; i < n; i++) {
        if ((subset & (1 << i)) != 0) {
          subset_list.push_back(nums[i]);
        }
      }

      result.push_back(subset_list);
    }

    return result;
  }
};
