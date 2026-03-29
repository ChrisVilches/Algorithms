#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxProduct(const vector<int>& nums) {
    array<int, 2> best{-1, -1};

    for (const int x : nums) {
      if (x > best.front()) {
        best[1] = best[0];
        best[0] = x;
      } else if (x > best.back()) {
        best[1] = x;
      }
    }

    return (best.front() - 1) * (best.back() - 1);
  }
};
