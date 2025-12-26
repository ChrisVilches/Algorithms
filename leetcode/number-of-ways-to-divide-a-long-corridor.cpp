#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;

 public:
  int numberOfWays(const string corridor) {
    int count = 0;
    long long prev_idx = -1;

    long long ans = 1;

    for (size_t i = 0; i < corridor.size(); i++) {
      if (corridor[i] != 'S') continue;

      count++;

      if (count % 2 == 0) {
        prev_idx = i;
      } else if (prev_idx != -1) {
        ans *= i - prev_idx;
        ans %= mod;
      }
    }

    if (count == 0 || count % 2 != 0) return 0;

    return ans;
  }
};
