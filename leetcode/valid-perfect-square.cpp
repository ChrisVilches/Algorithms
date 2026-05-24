#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isPerfectSquare(const int num) {
    int lo = 0;
    int hi = num;

    while (lo <= hi) {
      const long long mid = (lo + hi) / 2;
      if (mid * mid == num) return true;

      if (mid * mid > num) {
        hi = mid - 1;
      } else {
        lo = mid + 1;
      }
    }

    return false;
  }
};
