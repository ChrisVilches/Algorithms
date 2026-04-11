#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isTrionic(const vector<int>& nums) {
    int state = 0;

    if (nums[0] >= nums[1]) return false;

    for (size_t i = 0; i < nums.size() - 1; i++) {
      if (nums[i] == nums[i + 1]) return false;

      switch (state) {
        case 0:
          if (nums[i] > nums[i + 1]) state = 1;
          break;
        case 1:
          if (nums[i] < nums[i + 1]) state = 2;
          break;
        case 2:
          if (nums[i] > nums[i + 1]) return false;
          break;
      };
    }

    return state == 2;
  }
};
