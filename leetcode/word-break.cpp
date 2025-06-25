#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool wordBreak(const string s, const vector<string>& wordDict) {
    const int n = s.size();
    const unordered_set<string> dict{wordDict.begin(), wordDict.end()};

    vector<bool> dp(s.size(), false);
    dp.emplace_back(true);

    for (int i = n - 1; i >= 0; i--) {
      string curr = "";

      for (int j = i; j < n && !dp[i]; j++) {
        curr += s[j];
        dp[i] = dict.count(curr) && dp[j + 1];
      }
    }

    return dp[0];
  }
};
