#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> sortedSquares(vector<int>& nums) {
    int i = 0;
    int j = nums.size() - 1;

    vector<int> res(nums.size());
    int k = nums.size() - 1;

    while (i <= j) {
      const int a = nums[i] * nums[i];
      const int b = nums[j] * nums[j];
      if (a > b) {
        res[k--] = a;
        i++;
      } else {
        res[k--] = b;
        j--;
      }
    }

    return res;
  }
};
