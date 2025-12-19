#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minOperations(const vector<int>& nums, const int k) {
    return accumulate(nums.begin(), nums.end(), 0) % k;
  }
};
