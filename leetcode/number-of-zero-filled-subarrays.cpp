#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long zeroFilledSubarray(const vector<int>& nums) {
    long long ans = 0;
    long long count = 0;

    for (const int x : nums) {
      if (count > 0) {
        if (x == 0) {
          count++;
        } else {
          ans += count;
          ans += (count * (count - 1)) / 2;
          count = 0;
        }
      } else {
        if (x == 0) {
          count = 1;
        }
      }
    }

    ans += count;
    ans += (count * (count - 1)) / 2;

    return ans;
  }
};
