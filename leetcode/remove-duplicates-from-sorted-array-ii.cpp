#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int curr = INT_MAX;
    int count = 1;
    int k = 0;

    for (const int n : nums) {
      if (n != curr) {
        curr = n;
        count = 1;
      } else {
        count++;
      }

      nums[k] = curr;

      if (count <= 2) k++;
    }

    return k;
  }
};
