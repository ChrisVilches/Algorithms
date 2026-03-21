#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long sumAndMultiply(const int n) {
    long long concat = 0;
    long long sum = 0;

    for (int x = n, d = 1; x > 0; x /= 10) {
      const int digit = x % 10;
      if (digit == 0) continue;

      sum += digit;
      concat += d * digit;
      d *= 10;
    }

    return concat * sum;
  }
};
