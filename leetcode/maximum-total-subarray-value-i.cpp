#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long maxTotalValue(const vector<int>& nums, const int k) {
    const long long max_val = *max_element(nums.begin(), nums.end());
    const long long min_val = *min_element(nums.begin(), nums.end());

    return k * (max_val - min_val);
  }
};
