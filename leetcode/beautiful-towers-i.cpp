#include <bits/stdc++.h>
using namespace std;

class Solution {
  using ll = long long;

 public:
  long long maximumSumOfHeights(const vector<int>& heights) {
    const int n = heights.size();
    ll ans = 0;

    for (int i = 0; i < n; i++) {
      ll sum = heights[i];

      int curr = heights[i];

      for (int j = i + 1; j < n; j++) {
        curr = min(curr, heights[j]);
        sum += curr;
      }

      curr = heights[i];

      for (int j = i - 1; j >= 0; j--) {
        curr = min(curr, heights[j]);
        sum += curr;
      }

      ans = max(ans, sum);
    }

    return ans;
  }
};
