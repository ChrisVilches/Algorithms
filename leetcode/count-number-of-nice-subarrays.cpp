#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int numberOfSubarrays(const vector<int>& nums, const int target) {
    const int n = nums.size();

    int ans = 0;

    for (int i = 0, j = 0, k = 0, curr = 0; i < n; i++) {
      while (j < n && curr < target) {
        curr += nums[j] % 2 == 1;
        j++;
      }

      if (k < j) k = j;
      while (k < n && nums[k] % 2 == 0) k++;

      if (curr == target) {
        ans += k - j + 1;
      }

      curr -= nums[i] % 2 == 1;
    }

    return ans;
  }
};
