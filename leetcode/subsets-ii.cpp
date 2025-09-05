#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    const int n = nums.size();

    set<vector<int>> result;

    for (int subset = 0; subset < (1 << n); subset++) {
      vector<int> subset_list;

      for (int i = 0; i < n; i++) {
        if ((subset & (1 << i)) != 0) {
          subset_list.push_back(nums[i]);
        }
      }

      sort(subset_list.begin(), subset_list.end());
      result.insert(subset_list);
    }

    return vector<vector<int>>(result.begin(), result.end());
  }
};
