#include <bits/stdc++.h>
using namespace std;

class Solution {
  int num_reverse(const int x) const {
    string s = to_string(x);
    reverse(s.begin(), s.end());
    return stoi(s);
  }

 public:
  int minMirrorPairDistance(const vector<int>& nums) {
    unordered_map<int, int> last_idx;

    size_t ans = INT_MAX;

    for (size_t i = 0; i < nums.size(); i++) {
      const int x = nums[i];

      if (last_idx.count(x)) {
        ans = min(ans, i - last_idx[x]);
      }

      last_idx[num_reverse(nums[i])] = i;
    }

    return ans == INT_MAX ? -1 : ans;
  }
};
