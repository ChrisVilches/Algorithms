#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long largestPerimeter(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    long long ans = -1;
    long long sum = 0;

    for (const int curr : nums) {
      if (sum > curr) ans = max(ans, sum + curr);

      sum += curr;
    }

    return ans;
  }
};
