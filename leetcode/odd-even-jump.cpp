#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int oddEvenJumps(const vector<int>& arr) {
    const int n = arr.size();
    array<vector<bool>, 2> dp;
    fill(dp.begin(), dp.end(), vector<bool>(n, false));

    dp[0].back() = true;
    dp[1].back() = true;

    set<pair<int, int>> a{{arr.back(), n - 1}};
    set<pair<int, int>> b{{-arr.back(), n - 1}};

    for (int i = n - 2; i >= 0; i--) {
      const auto gte = a.lower_bound({arr[i], -1});
      const auto lte = b.lower_bound({-arr[i], -1});

      if (gte != a.end()) dp[0][i] = dp[1][gte->second];
      if (lte != b.end()) dp[1][i] = dp[0][lte->second];

      a.emplace(arr[i], i);
      b.emplace(-arr[i], i);
    }

    return accumulate(dp[0].begin(), dp[0].end(), 0);
  }
};
