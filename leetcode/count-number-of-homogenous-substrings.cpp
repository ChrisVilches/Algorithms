#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;

 public:
  int countHomogenous(const string s) {
    long long ans = 0;
    long long curr = 0;

    char prev = '$';

    for (const char c : s) {
      if (c == prev) {
        curr++;
      } else {
        prev = c;
        curr = 1;
      }

      ans += curr;
      ans %= mod;
    }

    return ans;
  }
};
