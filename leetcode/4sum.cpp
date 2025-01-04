#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> fourSum(const vector<int>& nums, const int target) {
    const int n = nums.size();
    set<vector<int>> res;

    vector<set<int>> sets;

    for (int i = 0; i < n; i++) {
      sets.emplace_back(set<int>{nums.begin() + i, nums.end()});
    }

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        for (int k = j + 1; k < n - 1; k++) {
          const long long sum = (long long)nums[i] + nums[j] + nums[k];
          if (sum > INT_MAX || sum < INT_MIN) continue;
          const int complement = target - sum;
          if (sets[k + 1].count(complement)) {
            vector<int> vec{nums[i], nums[j], nums[k], complement};
            sort(vec.begin(), vec.end());
            res.emplace(vec);
          }
        }
      }
    }

    return {res.begin(), res.end()};
  }
};
