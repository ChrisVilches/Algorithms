#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minOperations(const vector<int>& nums) {
    int ans = 0;

    unordered_map<int, int> prev_idx;
    stack<int> s;

    for (size_t i = 0; i < nums.size(); i++) {
      const int x = nums[i];

      while (!s.empty() && nums[s.top()] > x) s.pop();

      if (prev_idx.count(x)) {
        ans += !s.empty() && prev_idx[x] < s.top();
      } else if (x != 0) {
        ans++;
      }

      prev_idx[x] = i;
      s.emplace(i);
    }

    return ans;
  }
};
