#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;

 public:
  int specialTriplets(const vector<int>& nums) {
    unordered_map<int, long long> left, right;

    for (const int x : nums) {
      right[x]++;
    }

    long long ans = 0;

    for (const int x : nums) {
      right[x]--;

      ans += left[x * 2] * right[x * 2];
      ans %= mod;

      left[x]++;
    }

    return ans;
  }
};
