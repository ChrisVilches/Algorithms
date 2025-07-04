#include <bits/stdc++.h>
using namespace std;

class Solution {
  using pii = pair<int, int>;

 public:
  vector<int> secondGreaterElement(const vector<int>& nums) {
    const int n = nums.size();

    vector<int> ans(n, INT_MAX);
    vector<int> s;
    priority_queue<pii, vector<pii>, greater<pii>> q;

    for (int i = n - 1; i >= 0; i--) {
      while (!q.empty() && q.top().first <= nums[i]) q.pop();

      if (!q.empty()) ans[i] = q.top().second;

      while (!s.empty() && nums[i] >= nums[s.back()]) {
        const int idx = s.back();
        q.emplace(nums[idx], idx);
        s.pop_back();
      }

      if (s.size() >= 2) ans[i] = min(ans[i], s[s.size() - 2]);

      s.emplace_back(i);
    }

    for (int& x : ans) {
      x = x == INT_MAX ? -1 : nums[x];
    }

    return ans;
  }
};
