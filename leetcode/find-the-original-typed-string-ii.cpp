#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;

 public:
  int possibleStringCount(const string word, const int k) {
    vector<int> lengths;
    char prev = 0;

    for (const char c : word) {
      if (prev != c) {
        prev = c;
        lengths.emplace_back(0);
      }
      lengths.back()++;
    }

    vector<vector<int>> dp(2, vector<int>(k + 2));

    for (int i = k; i >= 0; i--) dp.back()[i] = max(0, lengths.back() - max(0, i - 1));
    partial_sum(dp.back().rbegin(), dp.back().rend(), dp.back().rbegin());

    long long mult = lengths.back();

    for (int i = lengths.size() - 2; i >= 0; i--) {
      if (i <= k) {
        for (int j = k; j >= 0; j--) {
          long long res = 0;

          res += max(0, lengths[i] - j) * mult;
          res += dp.back()[max(j - lengths[i], 0)] - dp.back()[j];
          res += dp.front()[j + 1];

          dp.front()[j] = (res + mod) % mod;
        }
      }

      mult = (mult * lengths[i]) % mod;
      swap(dp[0], dp[1]);
    }

    return dp.back()[k];
  }
};
