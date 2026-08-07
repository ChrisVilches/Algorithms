#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool uniformArray(const vector<int>& nums) {
    size_t sum = 0;

    for (const int x : nums) {
      sum += x & 1;
    }

    if (sum == 0 || sum == nums.size()) return true;

    return *min_element(nums.begin(), nums.end()) % 2 == 1;
  }
};
