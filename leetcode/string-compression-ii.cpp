#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<pair<char, int>> counts;
  int memo[101][101];

  int length(const int count) {
    if (count == 0) return 0;
    if (count == 1) return 1;
    if (count >= 100) return 4;
    if (count >= 10) return 3;
    return 2;
  }

  int dp(const int i, const int k) {
    const int n = counts.size();
    if (i == n) return 0;
    if (~memo[i][k]) return memo[i][k];

    int res = INT_MAX;

    int removed = 0;
    int count = 0;

    for (int j = i; j < n; j++) {
      if (counts[i].first == counts[j].first) {
        const int remaining = k - removed;
        count += counts[j].second;

        for (int del = 0; del <= remaining && del <= count; del++) {
          res = min(res, length(count - del) + dp(j + 1, remaining - del));
        }
      } else {
        removed += counts[j].second;
      }
    }

    return memo[i][k] = res;
  }

 public:
  int getLengthOfOptimalCompression(const string s, const int k) {
    memset(memo, -1, sizeof memo);

    for (const char c : s) {
      if (counts.empty() || counts.back().first != c) {
        counts.emplace_back(c, 0);
      }

      counts.back().second++;
    }

    return dp(0, k);
  }
};
