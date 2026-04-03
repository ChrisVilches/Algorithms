#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minimumDistance(const vector<int>& nums) {
    unordered_map<int, pair<int, int>> m;

    int ans = INT_MAX;

    for (size_t i = 0; i < nums.size(); i++) {
      const int x = nums[i];

      if (m.count(x) && m[x].second != -1) {
        ans = min(ans, 2 * int(i - m[x].first));

        m[x].first = m[x].second;
        m[x].second = i;
      } else if (m.count(x)) {
        m[x].second = i;
      } else {
        m[x] = {i, -1};
      }
    }

    return ans == INT_MAX ? -1 : ans;
  }
};
