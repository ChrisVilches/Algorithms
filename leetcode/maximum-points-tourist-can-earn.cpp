#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxScore(const int n, const int k, const vector<vector<int>>& stayScore,
               const vector<vector<int>>& travelScore) {
    vector<vector<int>> memo(k, vector<int>(n, -1));

    const function<int(int, int)> dp = [&](const int day, const int city) {
      if (day >= k) return 0;
      if (~memo[day][city]) return memo[day][city];

      const int stay = stayScore[day][city] + dp(day + 1, city);
      int travel = 0;

      for (int i = 0; i < n; i++) {
        if (i == city) continue;
        travel = max(travel, travelScore[city][i] + dp(day + 1, i));
      }

      return memo[day][city] = max(stay, travel);
    };

    int ans = 0;

    for (int i = 0; i < n; i++) {
      ans = max(ans, dp(0, i));
    }

    return ans;
  }
};
