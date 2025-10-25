#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int longestNiceSubarray(const vector<int>& nums) {
    size_t ans = 0;

    const auto valid = [&](const int from, const int to) {
      for (int i = from; i <= to; i++) {
        for (int j = i + 1; j <= to; j++) {
          if ((nums[i] & nums[j]) != 0) return false;
        }
      }
      return true;
    };

    for (size_t i = 0, j = 0; i < nums.size(); i++) {
      while (j < nums.size()) {
        if (!valid(i, j)) break;

        ans = max(ans, j - i + 1);
        j++;
      }
    }

    return ans;
  }
};
