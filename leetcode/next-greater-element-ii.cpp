#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> nextGreaterElements(const vector<int>& nums) {
    const int n = nums.size();

    vector<int> ans(n);

    stack<int> s;

    for (int i = 2 * n - 1; i >= 0; i--) {
      while (!s.empty() && nums[s.top() % n] <= nums[i % n]) s.pop();

      if (i < n) {
        ans[i] = s.empty() ? -1 : nums[s.top() % n];
      }

      s.push(i);
    }

    return ans;
  }
};
