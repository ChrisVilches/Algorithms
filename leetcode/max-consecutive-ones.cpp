#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findMaxConsecutiveOnes(vector<int>& nums) {
    int curr = 0;

    for (int& x : nums) {
      curr = (curr + 1) * x;
      x = curr;
    }

    return *max_element(nums.begin(), nums.end());
  }
};
