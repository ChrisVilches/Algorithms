#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxScoreSightseeingPair(vector<int>& values) {
    const int n = values.size();

    set<pair<int, int>> s;

    for (int i = 0; i < n; i++) {
      s.emplace(-(values[i] - i), i);
    }

    int ans = 0;

    for (int i = 0; i < n - 1; i++) {
      s.erase({-(values[i] - i), i});
      const auto [_, j] = *s.begin();
      ans = max(ans, values[i] + values[j] + i - j);
    }

    return ans;
  }
};
